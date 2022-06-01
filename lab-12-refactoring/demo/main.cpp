#include <boost/program_options.hpp>

#include "PageContainer.hpp"

namespace po = boost::program_options;

class CmdArgs {
 public:
  std::string input;
  float threshold = 0;

 public:
  void parse(int argc, char* argv[]) {
    // Add options
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help, h", "produce help message")
        ("input",
         po::value<std::string>(&input)
             ->default_value("../tests/InputExample.txt"),
         "path/to/input/file")
        ("threshold",
         po::value<float>(&threshold)->default_value(0.1),
         "threshold value");

    // Parse arguments
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << "Usage: demo [options]" << std::endl;
      std::cout << desc << std::endl;
    }
  }
};

int main(int argc, char* argv[]) {
  CmdArgs cmd;
  cmd.parse(argc, argv);

  auto* used_memory = new UsedMemory;
  auto* sender = new StatSender;
  PageContainer page(sender, used_memory);

  std::ifstream f_in(cmd.input);
  page.Load(f_in, cmd.threshold);
  f_in.close();

  Log::get_instance().Write(std::to_string(used_memory->used()));

  for (size_t i = 0; i < 5; ++i) {
    const auto& item = page.ByIndex(i);
    std::cout << item.name << ": " << item.score << std::endl;
    const auto& item2 = page.ById(std::to_string(i));
    std::cout << item2.name << ": " << item2.score << std::endl;
  }

  page.Reload(cmd.threshold);
  Log::get_instance().Write(std::to_string(used_memory->used()));

  return 0;
}

