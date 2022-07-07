//
// Created by Pascal Charpentier on 2022-07-02.
//

#include "gtest/gtest.h"
#include "tri.h"

class Tri_Test : public ::testing::Test {
protected:

    std::vector<std::vector<int> > test ;
    std::vector<std::vector<int> > solution ;

    void SetUp() override {
        test.emplace_back() ;
        solution.emplace_back() ;

        test.emplace_back(std::vector<int>{1}) ;
        solution.emplace_back(std::vector<int>{1}) ;

        test.emplace_back(std::vector<int>{1, 2}) ;
        solution.emplace_back(std::vector<int>{1, 2}) ;

        test.emplace_back(std::vector<int>{2, 1}) ;
        solution.emplace_back(std::vector<int>{1, 2}) ;

        test.emplace_back(std::vector<int>{1, 1}) ;
        solution.emplace_back(std::vector<int>{1, 1}) ;

        test.emplace_back(std::vector<int>{1, 2, 3}) ;
        solution.emplace_back(std::vector<int>{1, 2, 3}) ;

        test.emplace_back(std::vector<int>{2, 1, 3}) ;
        solution.emplace_back(std::vector<int>{1, 2, 3}) ;

        test.emplace_back(std::vector<int>{2, 1, 2}) ;
        solution.emplace_back(std::vector<int>{1, 2, 2}) ;

        test.emplace_back(std::vector<int>{2, 2, 2}) ;
        solution.emplace_back(std::vector<int>{2, 2, 2}) ;

        test.emplace_back(std::vector<int>{3, 2, 1}) ;
        solution.emplace_back(std::vector<int>{1, 2, 3}) ;

        test.emplace_back(std::vector<int>{2, 1, 3, 5, 9, 0, 4, 8, 7, 6}) ;
        solution.emplace_back(std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) ;

        test.emplace_back(std::vector<int>{2, 1, 4, 7, 7, 2, 8, 9, 0, 1, 5, 2, 9}) ;
        solution.emplace_back(std::vector<int>{0, 1, 1, 2, 2, 2, 4, 5, 7, 7, 8, 9, 9}) ;
    }


};

TEST_F(Tri_Test, tri_insertion) {

    for (auto i = 0; i< test.size(); ++i){
        tri_insertion<int>(test.at(i)) ;
        EXPECT_EQ(solution.at(i), test.at(i));
    }

}

TEST_F(Tri_Test, tri_fusion) {
    for (auto i = 0; i< test.size(); ++i){
        tri_fusion<int>(test.at(i)) ;
        EXPECT_EQ(solution.at(i), test.at(i));
    }

}

TEST_F(Tri_Test, tri_par_tas) {
    for (auto i = 0; i< test.size(); ++i){
        tri_par_tas<int>(test.at(i)) ;
        EXPECT_EQ(solution.at(i), test.at(i));
    }

}

TEST_F(Tri_Test, tri_bulle) {
    for (auto i = 0; i< test.size(); ++i){
        tri_bulle<int>(test.at(i)) ;
        EXPECT_EQ(solution.at(i), test.at(i));
    }

}

TEST_F(Tri_Test, tri_insertion_2) {
    for (auto i = 0; i< test.size(); ++i){
        tri_insertion_2<int>(test.at(i)) ;
        EXPECT_EQ(solution.at(i), test.at(i));
    }
}


TEST_F(Tri_Test, tri_rapide) {
    for (auto i = 0; i< test.size(); ++i){
        tri_rapide<int>(test.at(i)) ;
        EXPECT_EQ(solution.at(i), test.at(i));
    }

}