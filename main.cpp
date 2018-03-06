#include "binary_tree.h"

double plud(double m){
    cout<<m<<" ";
    return m;
}

double pr(double x) {
    std::cout << x<< std::endl;
    return x;
}
int main() {
        /*BinaryTree<int>* BT = new BinaryTree<int>();
        BT->insert(1,1);
        BT->insert(7,7);
        BT->insert(3,3);
        BT->insert(9,9);
        BT->insert(2,2);
    BT->Traverse(plud);
    cout<<endl;
        BT->remove(3);
        BT->remove(1);
    BT->Traverse(plud);
    cout<<endl;
        BT->insert(4,4);
        BT->Traverse(plud);
    cout<<endl;*/

    BinaryTree<double> tree = BinaryTree<double>();
    tree.insert(0, 10.2);
    tree.insert(3, 11.2);
    tree.insert(9, 12.2);
    tree.insert(5, 13.2);
    tree.insert(4, 14.2);
    tree.insert(8, 18.2);
    tree.insert(11, 111.2);
    tree.insert(10, 110.2);
    tree.insert(12, 112.2);
    cout << tree.find(5) << endl;
    tree.remove(9);
    tree.Traverse(plud);
    tree.remove(0);
    tree.remove(5);
    tree.remove(3);
    tree.remove(12);
    tree.remove(4);
    tree.remove(8);
    tree.remove(11);
    cout<<endl;
    tree.Traverse(plud);
    tree.remove(10);
    tree.~BinaryTree();
    tree.insert(2,12.2);
    cout<<endl;
    tree.Traverse(plud);
        return 0;
    }