#include "../Unity/src/unity.h"
#include "../c-vector/cvector.h"

#include "../src/scanner_helpers.h"

void setUp(void) {
}

void tearDown(void) {
}

void testCountDirsCurrentDirectory(void)
{
    char * dirName1 = "./test_dirs/0";
    tinydir_dir tinydir1;
    tinydir_open_sorted(&tinydir1, dirName1);

    TEST_ASSERT_TRUE(countDirsCurrentDirectory(tinydir1, dirName1) == 0);

    char * dirName2 = "./test_dirs/c";
    tinydir_dir tinydir2;
    tinydir_open_sorted(&tinydir2, dirName2);

    TEST_ASSERT_TRUE(countDirsCurrentDirectory(tinydir2, dirName2) == 2);

    char * dirName3 = "./test_dirs/c/c1/c2";
    tinydir_dir tinydir3;
    tinydir_open_sorted(&tinydir3, dirName3);

    TEST_ASSERT_TRUE(countDirsCurrentDirectory(tinydir3, dirName3) == 1);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
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

void test_0(void)
{
    char * dirName = "./test_dirs/0";
    tinydir_dir tinydir1;
    tinydir_open_sorted(&tinydir1, dirName);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName);

    tinydir_dir tinydir3;
    tinydir_open(&tinydir3, dirName);

    dirSummary summary0;
    unsigned int depth = countDirDepth(tinydir1);
    unsigned int d = countDirs(tinydir2);
    unsigned int f = countFiles(tinydir3);
    summary0.deepestDepth = depth;
    summary0.counts.directories = d;
    summary0.counts.files = f;

//    TEST_ASSERT_TRUE(summary0.deepestDepth == 1);
    TEST_ASSERT_TRUE(summary0.counts.files == 0);
    TEST_ASSERT_TRUE(summary0.counts.directories == 0);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}

void test_a(void)
{
    char * dirName = "./test_dirs/a";
    tinydir_dir tinydir1;
    tinydir_open_sorted(&tinydir1, dirName);

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

    TEST_ASSERT_TRUE(summaryA.deepestDepth == 1);
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
    tinydir_open_sorted(&tinydir1, dirName);

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

//    printf("%d\n", summaryC.deepestDepth);
//    TEST_ASSERT_TRUE(summaryC.deepestDepth == 4);
    TEST_ASSERT_TRUE(summaryC.counts.files == 2);
    TEST_ASSERT_TRUE(summaryC.counts.directories == 4);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}

void test_test_dirs(void)
{
    char * dirName = "./test_dirs/";
    tinydir_dir tinydir1;
    tinydir_open_sorted(&tinydir1, dirName);

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

//    printf("%d\n", summaryTest.deepestDepth);
//    TEST_ASSERT_TRUE(summaryTest.deepestDepth == 5);
    TEST_ASSERT_TRUE(summaryTest.counts.files == 5);
    TEST_ASSERT_TRUE(summaryTest.counts.directories == 8);

    tinydir_close(&tinydir1);
    tinydir_close(&tinydir2);
    tinydir_close(&tinydir3);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(testCountDirsCurrentDirectory);
    RUN_TEST(testVectorMax);
    RUN_TEST(test_0);
    RUN_TEST(test_a);
    RUN_TEST(test_c);
    RUN_TEST(test_test_dirs);

    return UNITY_END();
}
