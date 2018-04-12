#ifndef ALOGDAT_LABYRINTH_EDITORTEST_H
#define ALOGDAT_LABYRINTH_EDITORTEST_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class EditorTest : public ::testing::Test {
protected:
    EditorTest();

    virtual ~EditorTest();

    virtual void SetUp();

    virtual void TearDown();
};


#endif //ALOGDAT_LABYRINTH_EDITORTEST_H
