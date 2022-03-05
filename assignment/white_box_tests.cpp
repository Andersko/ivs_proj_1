//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Andrej Pavlovič <xpavlo14@stud.fit.vutbr.cz>
// $Date:       $2022-03-01
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Andrej Pavlovič
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

using namespace std;

class MatrixPreset : public ::testing::Test
{
protected:
    void SetUp() override {
        // Fill matrices with values
        medium.set(vector<vector<double>> {
                {4   , 3,  -8},
                {-9.0, -55, 2},
                {18  , 19,  19},
        });
        large.set(vector<vector<double>> {
                {0,         1,             2,             3,     4,        5},
                {0.0,       1.1,           2.2,           3.3,   4.4,      -999},
                {-5,        -4,            -3,            -2,    -1,       0},
                {-1000.01,  16,            16,            23,    -849,     65},
                {1000000.0, 1000001.10981, -1651556.4444, 19858, -651.789, 0.000001},
        });
    }

    Matrix small = Matrix();
    Matrix medium = Matrix(3, 3);
    Matrix large = Matrix(5, 6);
};

// Test constructor 1/2
TEST(MatrixConstructor, Matrix_1x1) {
    // Create matrix 1x1
    EXPECT_NO_THROW(Matrix());

    // Create matrix 1x1 and test its value
    EXPECT_EQ(Matrix().get(0, 0), 0);
}

// Test constructor 2/2
TEST(MatrixConstructor, Matrix_NxM) {
    // Class Matrix should throw exception
    EXPECT_THROW(Matrix(0, 0), runtime_error);

    // Class Vector should throw exception
    EXPECT_THROW(Matrix(-1, -1), length_error);
    EXPECT_THROW(Matrix(-10, -10), length_error);

    // Test constructor with different matrix sizes
    EXPECT_NO_THROW({
        // Define separately because in macro
        int n1 = 1; int n2 = 1; int n3 = 5; int n4 = 10;
        int m1 = 1; int m2 = 4; int m3 = 5; int m4 = 3;

        Matrix matrix1(n1, m1);
        Matrix matrix2(n2, m2);
        Matrix matrix3(n3, m3);
        Matrix matrix4(n4, m4);

        int i; int j;

        for (i = 0; i < n1; i++)
            for (j = 0; j < m1; j++)
                EXPECT_EQ(matrix1.get(i, j), 0);

        for (i = 0; i < n2; i++)
            for (j = 0; j < m2; j++)
                EXPECT_EQ(matrix2.get(i, j), 0);

        for (i = 0; i < n3; i++)
            for (j = 0; j < m3; j++)
                EXPECT_EQ(matrix3.get(i, j), 0);

        for (i = 0; i < n4; i++)
            for (j = 0; j < m4; j++)
                EXPECT_EQ(matrix4.get(i, j), 0);
    });
}

// Test set() 1/2
TEST_F(MatrixPreset, setOne) {
    EXPECT_EQ(small.get(0, 0), 0);
    EXPECT_TRUE(small.set(0, 0, -1.0));
    EXPECT_EQ(small.get(0, 0), -1);
    EXPECT_FALSE(small.set(1, 0, 15));

    EXPECT_EQ(medium.get(0, 0), 4);
    EXPECT_EQ(medium.get(2, 2), 19);
    EXPECT_TRUE(medium.set(0, 0, 1.0));
    EXPECT_TRUE(medium.set(2, 2, -11.89));
    EXPECT_EQ(medium.get(0, 0), 1.0);
    EXPECT_EQ(medium.get(2, 2), -11.89);
    EXPECT_FALSE(medium.set(1, 3, 0));
    EXPECT_FALSE(medium.set(-8, 0, -10));

    EXPECT_EQ(large.get(3, 2), 16);
    EXPECT_EQ(large.get(3, 5), 65);
    EXPECT_EQ(large.get(2, 1), -4);
    EXPECT_TRUE(large.set(3, 2, -16));
    EXPECT_TRUE(large.set(3, 5, -65.5));
    EXPECT_TRUE(large.set(2, 1, 4));
    EXPECT_EQ(large.get(3, 2), -16);
    EXPECT_EQ(large.get(3, 5), -65.5);
    EXPECT_EQ(large.get(2, 1), 4);
    EXPECT_FALSE(large.set(-1, -1, 15));
    EXPECT_FALSE(large.set(3, 6, 16));
    EXPECT_FALSE(large.set(8, 8, -1000498.256));
}

// Test set() 2/2
TEST_F(MatrixPreset, setMultiple) {
    EXPECT_EQ(small.get(0, 0), 0);
    EXPECT_EQ(medium.get(1, 0), -9);
    EXPECT_EQ(medium.get(0, 2), -8);
    EXPECT_EQ(large.get(1, 1), 1.1);
    EXPECT_EQ(large.get(2, 2), -3);

    EXPECT_TRUE(small.set(vector<vector<double>> {{10}}));
    EXPECT_TRUE(medium.set(vector<vector<double>> {
        {0   , 0,  -1.0009},
        {1645, 0,  0},
        {18  , 0,  -19},
    }));
    EXPECT_TRUE(large.set(vector<vector<double>> {
        {0,          0,              0,            0,      0,       0},
        {0.0,        1.2,            0,            -3.3,   -4.4,    0},
        {0,          0,              3,            0,      0,       0},
        {0,          0,              0,            0,      0,       0},
        {-1000000.0, -1000001.10981, 1651556.4444, -19858, 651.789, -0.000001},
    }));

    EXPECT_EQ(small.get(0, 0), 10);
    EXPECT_EQ(medium.get(1, 0), 1645);
    EXPECT_EQ(medium.get(0, 2), -1.0009);
    EXPECT_EQ(large.get(1, 1), 1.2);
    EXPECT_EQ(large.get(2, 2), 3);

    EXPECT_FALSE(small.set(vector<vector<double>> {{}}));
    EXPECT_FALSE(medium.set(vector<vector<double>> {
        {0,          0,              0,            0,      0,       0},
        {0.0,        1.2,            0,            -3.3,   -4.4,    0},
        {0,          0,              3,            0,      0,       0},
        {0,          0,              0,            0,      0,       0},
        {-1000000.0, -1000001.10981, 1651556.4444, -19858, 651.789, -0.000001},
    }));
    EXPECT_FALSE(large.set(vector<vector<double>> {
        {0   , 0,  -1.0009},
        {1645, 0,  0},
        {18  , 0,  -19},
    }));
}

// Test get()
TEST_F(MatrixPreset, get) {
    EXPECT_EQ(small.get(0, 0), 0);
    EXPECT_EQ(medium.get(1, 0), -9);
    EXPECT_EQ(medium.get(0, 2), -8);
    EXPECT_EQ(large.get(1, 1), 1.1);
    EXPECT_EQ(large.get(2, 2), -3);

    EXPECT_ANY_THROW(small.get(-1, 0));
    EXPECT_ANY_THROW(medium.get(1, 8));
    EXPECT_ANY_THROW(large.get(1, 188));
}

// Test operator==()
TEST_F(MatrixPreset, equalMethod) {
    EXPECT_NO_THROW({
        // Compare same size matrices with same values
        EXPECT_TRUE(small.operator==(small));
        EXPECT_TRUE(medium.operator==(medium));
        EXPECT_TRUE(large.operator==(large));

        // Compare same size matrices with different values
        Matrix small2 = Matrix();
        Matrix medium2 = Matrix(3, 3);
        Matrix large2 = Matrix(5, 6);

        small2.set(vector<vector<double>> {{-199.89}});

        // Flip x and y
        medium2.set(vector<vector<double>> {
            {4,  -9.0, 18},
            {3,  -55,  19},
            {-8, 2,    19},
        });

        // Change just one value (4, 4)
        large.set(vector<vector<double>> {
            {0,         1,             2,             3,     4,        5},
            {0.0,       1.1,           2.2,           3.3,   4.4,      -999},
            {-5,        -4,            -3,            -2,    -1,       0},
            {-1000.01,  16,            16,            23,    -849,     65},
            {1000000.0, 1000001.10981, -1651556.4444, 19858, -650.789, 0.000001},
        });

        EXPECT_FALSE(small.operator==(small2));
        EXPECT_FALSE(medium.operator==(medium2));
        EXPECT_FALSE(large.operator==(large2));
    });

    EXPECT_THROW(small.operator==(medium), runtime_error);
    EXPECT_THROW(small.operator==(large), runtime_error);
    EXPECT_THROW(medium.operator==(small), runtime_error);
    EXPECT_THROW(medium.operator==(large), runtime_error);
    EXPECT_THROW(large.operator==(small), runtime_error);
    EXPECT_THROW(large.operator==(medium), runtime_error);
}

// Test operator+()
TEST_F(MatrixPreset, sumMethod) {
    EXPECT_NO_THROW({
        // Matrices with doubled values with sum function
        Matrix small2 = small.operator+(small);
        Matrix medium2 = medium.operator+(medium);
        Matrix large2 = large.operator+(large);

        // Matrices with doubled values manually
        Matrix small3 = Matrix();
        Matrix medium3 = Matrix(3, 3);
        Matrix large3 = Matrix(5, 6);

        // Double values manually
        EXPECT_TRUE(medium3.set(vector<vector<double>> {
            {4*2   , 3*2,  -8*2},
            {-9.0*2, -55*2, 2*2},
            {18*2  , 19*2,  19*2},
        }));
        EXPECT_TRUE(large3.set({
            {0*2,         1*2,             2*2,             3*2,     4*2,        5*2},
            {0.0*2,       1.1*2,           2.2*2,           3.3*2,   4.4*2,      -999*2},
            {-5*2,        -4*2,            -3*2,            -2*2,    -1*2,       0*2},
            {-1000.01*2,  16*2,            16*2,            23*2,    -849*2,     65*2},
            {1000000.0*2, 1000001.10981*2, -1651556.4444*2, 19858*2, -651.789*2, 0.000001*2},
        }));

        EXPECT_TRUE(small2.operator==(small3));
        EXPECT_TRUE(medium2.operator==(medium3));
        EXPECT_TRUE(large2.operator==(large3));

        EXPECT_TRUE(small.operator==(small2)); // TRUE because '0 + 0 = 0'
        EXPECT_FALSE(medium.operator==(medium2));
        EXPECT_FALSE(large.operator==(large2));
    });

    EXPECT_THROW(small.operator+(medium), runtime_error);
    EXPECT_THROW(small.operator+(large), runtime_error);
    EXPECT_THROW(medium.operator+(small), runtime_error);
    EXPECT_THROW(medium.operator+(large), runtime_error);
    EXPECT_THROW(large.operator+(small), runtime_error);
    EXPECT_THROW(large.operator+(medium), runtime_error);
}

// Test operator*() 1/2
TEST_F(MatrixPreset, multiplyMethod) {

}

// Test operator*() 2/2
TEST_F(MatrixPreset, multiplyMethod) {

}

/*** Konec souboru white_box_tests.cpp ***/
