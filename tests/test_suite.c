#include "../Unity/src/unity.h"
#include "../c-vector/cvector.h"

#include "../src/scanner_helpers.h"

void setUp(void) {
}

void tearDown(void) {
}

void testVectorMax(void)
{
    cvector_vector_type(int) v1 = NULL;
    cvector_push_back(v1, 40);

    TEST_ASSERT_TRUE(vectorMax(v1) == 40);

    cvector_vector_type(unsigned int) v2 = NULL;
    cvector_push_back(v2, 1000);
    cvector_push_back(v2, 220);
    cvector_push_back(v2, 380);
    cvector_push_back(v2, 407);

    TEST_ASSERT_TRUE(vectorMax(v2) == 1000);

    cvector_free(v1);
    cvector_free(v2);
}

void test_a(void)
{
    char * dirName = "./test_dirs/a";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName);

    tinydir_dir tinydir3;
    tinydir_open(&tinydir3, dirName);

    dirSummary summaryA;
    unsigned int depth = countDirDepth(tinydir1);
    unsigned int d = countDirs(tinydir2);
    unsigned int f = countFiles(tinydir3);
    summaryA.deepestDepth = depth;
    summaryA.counts.directories = d;
    summaryA.counts.files = f;

    TEST_ASSERT_TRUE(summaryA.deepestDepth == 0);
    TEST_ASSERT_TRUE(summaryA.counts.files == 1);
    TEST_ASSERT_TRUE(summaryA.counts.directories == 0);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}

void test_c(void)
{
    char * dirName = "./test_dirs/c";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName);

    tinydir_dir tinydir3;
    tinydir_open(&tinydir3, dirName);

    dirSummary summaryC;
    unsigned int depth = countDirDepth(tinydir1);
    unsigned int d = countDirs(tinydir2);
    unsigned int f = countFiles(tinydir3);
    summaryC.deepestDepth = depth;
    summaryC.counts.directories = d;
    summaryC.counts.files = f;

    TEST_ASSERT_TRUE(summaryC.deepestDepth == 1);
    TEST_ASSERT_TRUE(summaryC.counts.files == 2);
    TEST_ASSERT_TRUE(summaryC.counts.directories == 1);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}


void test_e(void)
{
    char * dirName = "./test_dirs/e";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName);

    tinydir_dir tinydir3;
    tinydir_open(&tinydir3, dirName);

    dirSummary summaryE;
    unsigned int depth = countDirDepth(tinydir1);
    unsigned int d = countDirs(tinydir2);
    unsigned int f = countFiles(tinydir3);
    summaryE.deepestDepth = depth;
    summaryE.counts.directories = d;
    summaryE.counts.files = f;

    TEST_ASSERT_TRUE(summaryE.deepestDepth == 3);
    TEST_ASSERT_TRUE(summaryE.counts.files == 4);
    TEST_ASSERT_TRUE(summaryE.counts.directories == 4);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}

void test_test_dirs(void)
{
    char * dirName = "./test_dirs";
    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName);

    tinydir_dir tinydir3;
    tinydir_open(&tinydir3, dirName);

    dirSummary summaryTest;
    unsigned int depth = countDirDepth(tinydir1);
    unsigned int d = countDirs(tinydir2);
    unsigned int f = countFiles(tinydir3);
    summaryTest.deepestDepth = depth;
    summaryTest.counts.directories = d;
    summaryTest.counts.files = f;

    TEST_ASSERT_TRUE(summaryTest.deepestDepth == 4);
    TEST_ASSERT_TRUE(summaryTest.counts.files == 10);
    TEST_ASSERT_TRUE(summaryTest.counts.directories == 9);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(testVectorMax);
    RUN_TEST(test_a);
    RUN_TEST(test_c);
    RUN_TEST(test_e);
    RUN_TEST(test_test_dirs);

    return UNITY_END();
}
