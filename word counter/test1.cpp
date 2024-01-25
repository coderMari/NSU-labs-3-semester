#include "world_counter.h"
#include <string>

#include "gtest/gtest.h"

TEST(TaskTest, writeResult) {

	ifstream in("test1.txt");
	ofstream out("out.csv");
	string line, outline;
	WordCounter counter;
	counter.process(in);
	counter.writeResult(out);

	in.close();
	out.close();

	ifstream test("test1.csv");
	ifstream outf("out.csv");

	while (getline(outf, line)) {

		getline(test, outline);
		ASSERT_EQ(line,outline);
	}
	in.close();
	outf.close();

}