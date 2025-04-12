#include "gtest.h"
#include "polynomials.h"
#include "string"

using namespace std;

class MonomTesting : public ::testing::Test
{

protected:
    Monom* m;
public:
    void SetUp() { m = new Monom(267, 5.1); }
    void TearDown() { delete m; }
};

TEST(MonomTest, can_create_zero_monom)
{
    ASSERT_NO_THROW(Monom m);
}

TEST(MonomTest, can_create_monom)
{
    ASSERT_NO_THROW(Monom m(52, 3.8));
}

TEST(MonomTest, cant_create_monom_with_too_large_degree)
{
    ASSERT_ANY_THROW(Monom(1111, 5));
}

TEST_F(MonomTesting, can_get_x_degree)
{
    EXPECT_EQ(this->m->x_deg(), 2);
}

TEST_F(MonomTesting, can_get_y_degree)
{
    EXPECT_EQ(this->m->y_deg(), 6);
}

TEST_F(MonomTesting, can_get_z_degree)
{
    EXPECT_EQ(this->m->z_deg(), 7);
}

TEST_F(MonomTesting, can_check_degree_is_correct)
{
    EXPECT_TRUE(this->m->is_deg_correct());
}

TEST_F(MonomTesting, can_add_monoms)
{
    Monom op(267, 1.6);
    Monom res = *(this->m) + op;
    EXPECT_EQ(res.get_deg(), 267);
    EXPECT_DOUBLE_EQ(res.get_c(), 6.7);
}

TEST_F(MonomTesting, cant_add_monoms_with_diff_pows)
{
    Monom op(324, 1.6);
    ASSERT_ANY_THROW(*(this->m) + op);
}

TEST_F(MonomTesting, addiction_can_create_zero_monom)
{
    Monom op(267, -5.1);
    Monom res = *(this->m) + op;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_c(), 0);
}

TEST_F(MonomTesting, can_dif_monoms)
{
    Monom op(267, 1.3);
    Monom res = *(this->m) - op;
    EXPECT_EQ(res.get_deg(), 267);
    EXPECT_DOUBLE_EQ(res.get_c(), 3.8);
}

TEST_F(MonomTesting, cant_dif_monoms_with_diff_pows)
{
    Monom op(324, 1.3);
    ASSERT_ANY_THROW(*(this->m) - op);
}

TEST_F(MonomTesting, dif_can_create_zero_monom)
{
    Monom op(267, 5.1);
    Monom res = *(this->m) - op;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_c(), 0);
}

TEST_F(MonomTesting, can_mult_with_scalar)
{
    Monom res = *(this->m) * 5;
    EXPECT_EQ(res.get_deg(), 267);
    EXPECT_EQ(res.get_c(), 25.5);
}

TEST_F(MonomTesting, can_mult_with_zero_scalar)
{
    Monom res = *(this->m) * 0;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_c(), 0);
}

TEST_F(MonomTesting, can_mult_monoms)
{
    Monom op(431, 3);
    Monom res = *(this->m) * op;
    EXPECT_EQ(res.get_deg(), 698);
    EXPECT_DOUBLE_EQ(res.get_c(), 15.3);
}

TEST_F(MonomTesting, mult_throw_when_degree_is_out_of_range)
{
    Monom op(452, 3);
    ASSERT_ANY_THROW(*(this->m) * op);
}

TEST_F(MonomTesting, mult_can_create_zero_monom)
{
    Monom op(431, 0);
    Monom res = *(this->m) * op;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_c(), 0);
}

class PolynomTesting : public ::testing::Test
{
protected:
    Polynom* p1, * p2;
    
public:
    void SetUp()
    {
        p1 = new Polynom;
        (*p1).push_back(Monom(344, -4));
        (*p1).push_back(Monom(135, 1.5));
        p2 = new Polynom;
        (*p2).push_back(Monom(344, 1));
        (*p2).push_back(Monom(530, -7));
        (*p2).push_back(Monom(100, 0.46));

    }
    void TearDown()
    {
        delete p1;
        delete p2;
    }
};

TEST(PolynomTest, can_create_polynom)
{
    ASSERT_NO_THROW(Polynom p);
}

TEST_F(PolynomTesting, can_add_polynoms)
{
    Polynom res = *(this->p1) + *(this->p2);
    List<Monom>::iterator it = res.begin().get_current()->next;

    EXPECT_EQ((*it).get_deg(), 344);
    EXPECT_EQ((*it).get_c(), -3);

    ++it;
    EXPECT_EQ((*it).get_deg(), 530);
    EXPECT_EQ((*it).get_c(), -7);

    ++it;
    EXPECT_EQ((*it).get_deg(), 135);
    EXPECT_EQ((*it).get_c(), 1.5);

    ++it;
    EXPECT_EQ((*it).get_deg(), 100);
    EXPECT_EQ((*it).get_c(), 0.46);
}

TEST_F(PolynomTesting, can_mult_with_scalar)
{
    Polynom res = *(this->p1) * 2;

    List<Monom>::iterator it = res.begin().get_current()->next;
    EXPECT_EQ((*it).get_deg(), 344);
    EXPECT_EQ((*it).get_c(), -8);

    ++it;
    EXPECT_EQ((*it).get_deg(), 135);
    EXPECT_EQ((*it).get_c(), 3);
}


TEST_F(PolynomTesting, can_mult_polynoms)
{
    Polynom res = *(this->p1) * *(this->p2);
    List<Monom>::iterator it = res.begin().get_current()->next;
    EXPECT_EQ((*it).get_deg(), 688);
    EXPECT_DOUBLE_EQ((*it).get_c(), -4);

    ++it;
    EXPECT_EQ((*it).get_deg(), 874);
    EXPECT_DOUBLE_EQ((*it).get_c(), 28);

    ++it;
    EXPECT_EQ((*it).get_deg(), 479);
    EXPECT_DOUBLE_EQ((*it).get_c(), 1.5);

    ++it;
    EXPECT_EQ((*it).get_deg(), 665);
    EXPECT_DOUBLE_EQ((*it).get_c(), -10.5);

    ++it;
    EXPECT_EQ((*it).get_deg(), 444);
    EXPECT_DOUBLE_EQ((*it).get_c(), -1.84);

    ++it;
    EXPECT_EQ((*it).get_deg(), 235);
    EXPECT_DOUBLE_EQ((*it).get_c(), 0.69);
}