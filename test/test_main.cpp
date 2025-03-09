#include <gtest.h>
#include <DataBaseVector.h>
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
//    DataBaseVector *db = new DataBaseVector("2x^4y^3z^2+6x^4y^7z^2+2x^2y^3z^2");
//    db->print();
//    db->sort();
//    db->print();
//
//    Monom m("6x^4y^3z^2");
//    db->insert(m);
//    db->print();
//
//    //db->erase(m);
//    //db->print();
//
//    std::cout << db->find(m) << std::endl;
//    return 0;
}
