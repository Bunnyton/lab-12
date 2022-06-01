// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include <stdexcept>
#include <thread>

#include <gmock/gmock.h>

#include "PageContainer.hpp"

class MockStatSender: public StatSender {
 public:
  MOCK_METHOD(void, AsyncSend,
              (const std::vector<Item> &items, std::string_view path),
              (override));
};


TEST(PageContainer, Test_1) {
  size_t size;
  float threshold = 0.1;
  PageContainer page;

  std::ifstream f_in("../tests/InputExample.txt");
  if (!f_in.is_open()) throw;
  page.Load(f_in, threshold);
  f_in.close();
  size = page.get_size();

  f_in.open("../tests/data1.txt");
  if (!f_in.is_open()) throw;
  EXPECT_ANY_THROW(page.Load(f_in, threshold));
  f_in.close();

  EXPECT_EQ(size, page.get_size());
}


TEST(PageContainer, Test_2) {
  using ::testing::_;
  using ::testing::AtLeast;
  auto* sender = new MockStatSender;

  float threshold = 0.1;
  PageContainer page(sender);

  std::ifstream f_in("../tests/InputExample.txt");
  if (!f_in.is_open()) throw;
  EXPECT_CALL(*sender, AsyncSend(_, _)).Times(4);

  page.Load(f_in, threshold);
  f_in.close();
}

TEST(UsedMemory, Test_1) {
  std::string test_str = "1 Иван 1.6";
  Item item;
  item.name = "Иван";
  item.id = "1";
  item.score = 1.6;
  size_t mem = item.name.capacity() + item.id.capacity() + sizeof(item.score);

  UsedMemory used_mem;

  used_mem.OnRawDataLoaded({}, {test_str});
  EXPECT_EQ(test_str.capacity(), used_mem.used());

  used_mem.OnDataLoaded({}, {item});
  EXPECT_EQ(mem + test_str.capacity(), used_mem.used());
}

TEST(Histogram, Test_1) {
  float threshold = 0.1;
  auto* sender = new StatSender;
  auto* used_mem = new UsedMemory;
  auto* hist = new Histogram;
  PageContainer page(sender, used_mem, hist);

  std::ifstream f_in("../tests/InputExample.txt");
  if (!f_in.is_open()) throw;
  page.Load(f_in, threshold);
  f_in.close();

  EXPECT_EQ(3, hist->get_skipped());
}

TEST(Data, Test_1) {
  std::ifstream f_in;
  float threshold = 0.1;
  PageContainer page;

  EXPECT_ANY_THROW(page.Load(f_in, threshold));
}

TEST(Data, Test_2) {
  float threshold = 0.1;
  PageContainer page;

  std::ifstream f_in("../tests/data1.txt");
  if (!f_in.is_open()) throw;
  EXPECT_ANY_THROW(page.Load(f_in, threshold));
  f_in.close();
}

TEST(Data, Test_3) {
  using ::testing::_;
  using ::testing::AtLeast;
  float threshold = 0.1;
  auto* sender = new MockStatSender;
  PageContainer page(sender);

  std::ifstream f_in("../tests/data2.txt");
  if (!f_in.is_open()) throw;
  EXPECT_CALL(*sender, AsyncSend(_, _)).Times(12);
  EXPECT_ANY_THROW(page.Load(f_in, threshold));
  f_in.close();
}
