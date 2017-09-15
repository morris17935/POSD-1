#ifndef UTSORT_H_INCLUDED
#define UTSORT_H_INCLUDED
#include <list>
#include <algorithm>
template <class Type>
void swap (Type &a, Type &b){
    Type temp;
    temp = a;
    a = b;
    b = temp;
}

class IncreasingByDistanceToN
{
public:
    IncreasingByDistanceToN(int i):n(i){}
    int n;
    bool operator() (int i, int j){
        return abs(i - n) < abs(j - n);
    }
};

template <class Type>
class DecreasingByDistanceToN
{
public:
    DecreasingByDistanceToN(Type i):n(i){}
    Type n;
    bool operator() (Type i, Type j){
        return abs(i - n) > abs(j - n);
    }
};

template <class Type, class Comp>
void bubble (Type a[], int s, Comp comp){
    for(int j = 1; j <= s-1; j++){
        for (int i = s-1; i>=j; i--){
            if (comp(a[i],a[i-1])) //call the function
                swap(a[i],a[i-1]);
        }
    }
}



bool lessThan(int a, int b){
    return a < b;
}

bool greaterThan(int a, int b){
    return a > b;
}

TEST (swap, swapDouble){
    double a = 1.0, b = 2.0;
    swap(a, b);
    EXPECT_EQ(2.0, a);
    EXPECT_EQ(1.0, b);
}

TEST (Bubble, increasing){
    int a[5]= {5,2,43,6,9};
    bubble (a, 5, lessThan);

    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(5, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);
}

TEST (Bubble, decreasingFunction){
    int a[5]= {5,2,43,6,9};
    bubble(a, 5, greaterThan);

    ASSERT_EQ(43, a[0]);
    ASSERT_EQ(9, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(5, a[3]);
    ASSERT_EQ(2, a[4]);
}

TEST (Bubble, IncreasingByDistanceToN){
    int a[5]= {5,2,43,6,9};
    bubble (a, 5, IncreasingByDistanceToN(5));

    ASSERT_EQ(5, a[0]);
    ASSERT_EQ(6, a[1]);
    ASSERT_EQ(2, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);
}

TEST (Bubble, DecreasingByDistanceToN){
    int a[5]= {5,2,43,6,9};
    bubble (a, 5, DecreasingByDistanceToN<int>(5));

    ASSERT_EQ(43, a[0]);
    ASSERT_EQ(9, a[1]);
    ASSERT_EQ(2, a[2]);
    ASSERT_EQ(6, a[3]);
    ASSERT_EQ(5, a[4]);
}

TEST (Bubble, DecreasingByDistanceToD){
    double a[5]= {5.0, 2.0, 43.0, 6.0, 9.0};
    bubble (a, 5, DecreasingByDistanceToN<double>(5.0));

    ASSERT_EQ(43, a[0]);
    ASSERT_EQ(9, a[1]);
    ASSERT_EQ(2, a[2]);
    ASSERT_EQ(6, a[3]);
    ASSERT_EQ(5, a[4]);
}

TEST (Bubble, increasingLambda){
    int a[5]= {5,2,43,6,9};
    bubble (a, 5, [](int a, int b){return a < b;});

    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(5, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);
}

TEST (Bubble, DecreasingByDistanceToNLambda){
    int a[5]= {5,2,43,6,9};
    int n = 5;
    bubble (a, 5, [n](int a, int b){return abs(a-n) > abs(b-n);});

    ASSERT_EQ(43, a[0]);
    ASSERT_EQ(9, a[1]);
    ASSERT_EQ(2, a[2]);
    ASSERT_EQ(6, a[3]);
    ASSERT_EQ(5, a[4]);
}

TEST(sort, normalArray){
    int a[5]={5,2,43,6,9};
    std::sort(a,a+5);

    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(5, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);

}

TEST(sort, vector){
    std::vector<int> a;
    a.push_back(5);
    a.push_back(2);
    a.push_back(43);
    a.push_back(6);
    a.push_back(9);

    std::sort(a.begin(),a.end());

    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(5, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);

}

template <class Iter, class Comp>
void bubble2 (Iter first, Iter last, Comp comp){
    for(Iter j = first; j < last; j++){
        for (Iter i = last-1; i>j; i--){
            if (comp(*i,*(i-1)))
                swap(*i,*(i-1));
        }
    }
}


TEST(bubble2, normalArray){
    int a[5]={5,2,43,6,9};
    bubble2(a,a+5, [](int a, int b){return a<b;});

    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(5, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);

}

TEST(bubble2, vector){
    int b[5]={5,2,43,6,9};
    std::vector<int> a(b,b+5);

    bubble2(a.begin(),a.end(), [](int a, int b){return a<b;});

    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(5, a[1]);
    ASSERT_EQ(6, a[2]);
    ASSERT_EQ(9, a[3]);
    ASSERT_EQ(43, a[4]);

}
TEST(bubble2, list){
    int b[5]={5,2,43,6,9};
    std::list<int> a(b,b+5);

    /* cannot sort list because list creates bidirectional iterators,
    not RandomAccessIterators!

    bubble2(a.begin(),a.end(), [](int a, int b){return a<b;});

    */
}
#endif // UTSORT_H_INCLUDED
