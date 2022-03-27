#include "../Unity/src/unity.h"
#include "../src/scanner_helpers.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_0(void) {
    char * dirName0 = "./test_dirs/0";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName0);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName0);

    dirSummary summary0;
    unsigned int d = countDirs(tinydir1);
    unsigned int f = countFiles(tinydir2);
    summary0.counts.directories = d;
    summary0.counts.files = f;

    TEST_ASSERT_TRUE(summary0.counts.files == 0);
    TEST_ASSERT_TRUE(summary0.counts.directories == 0);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
}

void test_a(void)
{
    char * dirName3 = "./test_dirs/a";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName3);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName3);

    dirSummary summaryA;
    unsigned int d = countDirs(tinydir1);
    unsigned int f = countFiles(tinydir2);
    summaryA.counts.directories = d;
    summaryA.counts.files = f;

    TEST_ASSERT_TRUE(summaryA.counts.files == 1);
    TEST_ASSERT_TRUE(summaryA.counts.directories == 0);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
}

void test_c(void)
{
    char * dirName2 = "./test_dirs/c";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName2);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName2);

    dirSummary summaryC;
    unsigned int d = countDirs(tinydir1);
    unsigned int f = countFiles(tinydir2);
    summaryC.counts.directories = d;
    summaryC.counts.files = f;

    TEST_ASSERT_TRUE(summaryC.counts.files == 2);
    TEST_ASSERT_TRUE(summaryC.counts.directories == 4);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
}

void test_test_dirs(void)
{
    char * dirName3 = "./test_dirs/";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName3);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName3);

    dirSummary summaryTest;
    unsigned int d = countDirs(tinydir1);
    unsigned int f = countFiles(tinydir2);
    summaryTest.counts.directories = d;
    summaryTest.counts.files = f;

    TEST_ASSERT_TRUE(summaryTest.counts.files == 5);
    TEST_ASSERT_TRUE(summaryTest.counts.directories == 8);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_0);
    RUN_TEST(test_a);
    RUN_TEST(test_c);
    RUN_TEST(test_test_dirs);

    return UNITY_END();
}
