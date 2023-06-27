// Pendataan Peserta Olimpiade Matematika
// Kelompok 13 Strukdat J
// Bagas Maulana Akbar 21081010307
// Tedi Krisna Royyan Shofi 21081010325
// Muhammad Dava Satria Kurnianto 20081010133

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

typedef struct Node{
    int id;
    int height;
    string nama, asalkota;
    Node *left;
    Node *right;
};

Node *tree = NULL;
void insert (Node **root, int idbaru, string namabaru,string asalkotabaru){
    
if((*root)==NULL){
    Node *baru;
    baru = new Node;
    baru->id = idbaru;
    baru->nama = namabaru;
    baru->asalkota = asalkotabaru;
    baru->left = NULL;
    baru->right = NULL;
    (*root) = baru;
    (*root) -> left = NULL;
    (*root) -> right = NULL;
    cout << "Data Telah di Tambahkan!"<<endl;
    cout <<"Tekan Enter untuk Kembali ke Menu";
    
}    
else if(idbaru<(*root)->id)
    insert(&(*root)->left,idbaru,namabaru,asalkotabaru);

else if(idbaru>(*root)->id)
    insert(&(*root)->right,idbaru,namabaru,asalkotabaru);
        
else if(idbaru==(*root)->id)
    cout << "Data Sudah ada! ";  
}

//Menambahkan Node AVL
Node* newNode(int id, string namabaru, string asalkotabaru){
	Node* node = new Node;
	node->id = id;
    node->nama = namabaru;
    node->asalkota = asalkotabaru;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

//Untuk Mendapatkan Maximum 2 Integer
int max(int a, int b){
    return (a > b) ? a : b;
}
int max(int a, int b);

//Untuk Mendapatkan Tinggi
int height(struct Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

//Untuk Membuat Rotasi Kanan
struct Node *rightRotate(struct Node *y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), 
					height(y->right)) + 1;
    x->height = max(height(x->left), 
					height(x->right)) + 1;
    return x;
}

//Untuk Membuat Rotasi Kiri
struct Node *leftRotate(struct Node *x){
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), 
					height(x->right)) + 1;
    y->height = max(height(y->left), 
					height(y->right)) + 1;
    return y;
}

//Balance
int getBalance(struct Node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node *minValueNode(struct Node *node){
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

//Fungsi Menambahkan Node ke AVL
struct Node* insertAVL(struct Node* node, int id,string nama,string asalkota){
	//Insert Normal
	if (node == NULL){
		return(newNode(id,nama, asalkota));
    }
	if (id < node->id){
		node->left = insertAVL(node->left, id,nama,asalkota);
    }
	else if (id > node->id){
		node->right = insertAVL(node->right, id,nama,asalkota);
    }
	else 
		return node;

	//update height ancest
	node->height = 1 + max(height(node->left),
						height(node->right));
						
	//Untuk Balancing Node
	int balance = getBalance(node);

	//Dilakukan 4 Kemungkinan jika Node tidak Balance
	if (balance > 1 && id < node->left->id){
		return rightRotate(node);
    }
	if (balance < -1 && id > node->right->id){
		return leftRotate(node);
    }
	if (balance > 1 && id > node->left->id)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && id < node->right->id)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	cout << "Data Telah di Tambahkan!"<<endl;
    cout <<"Tekan Enter untuk Kembali ke Menu";
	return node;
	
}

Node* deleteBST(struct Node* root, int id)
{
    if (root == NULL)
        return root;
        
    //Jika ID lebih kecil drpd Root
    if (id < root->id)
        root->left = deleteBST(root->left, id);
        
    //Jika ID lebih besar drpd Root
    else if (id > root->id)
        root->right = deleteBST(root->right, id);
	
	//Jika ID sama besar dengan Root
    else {
    	//Tidak ada node atau node dengan satu anak
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
 	
 	//Node dengan dua anak
    Node* temp = minValueNode(root->right);
    root->id = temp->id;
        root->right = deleteBST(root->right, temp->id);
    }
    cout << "Data Telah di Hapus!"<<endl;
    cout <<"Tekan Enter untuk Kembali ke Menu";
    return root;
}

//Fungsi untuk Delete Node
Node *deleteNode(struct Node *root, int id){
	if (root == NULL)
        return root;
    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else if (id == root->id)
    {
         if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               
                *root = *temp; 
            free(temp);
        }
        else
        {
            struct Node *temp = minValueNode(root->right);
            root->id = temp->id;
            root->right = deleteNode(root->right, temp->id);
        }
    } 
    
    //Balance AVL
    if (root == NULL){
        return root;
}
        
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); 
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); 
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    cout << "Data Telah di Hapus!"<<endl;
    cout <<"Tekan Enter untuk Kembali ke Menu";
    return root;
}

//Menampilkan Data dari Node
void preOrder(Node *root){
    if(root!=NULL)
	{
        if (root->id != NULL)
        {
            cout << " " << root->id ;
            cout << "\t" << root->nama ; 
            cout << "\t\t" << root->asalkota <<endl;
        }
        preOrder(root->left);
        preOrder(root->right);
        
    }
}

//Mencari Data 
void search(Node *root, int id)
{
    if (root != NULL)
    {
        if (id == root->id)
        {
            cout << " " << root->id;
            cout << " \t" << root->nama;
            cout << " \t\t" << root->asalkota << endl;
            
        }
        else if (id < root->id)
        {
            search(root->left, id);
        }
        else if (id > root->id)
        {
            search(root->right, id);
        }
        
    }else
        {
            cout << "Data Tidak Ada";
        }
}

int main()
{
	char pil;
    int del,cari;
    while (true)
    {
        int id,hapus;
        string nama,asalkota;
        system("cls");
        cout<< "\t\t\t\t\tData Peserta Olimpiade MTK";
        cout<< "\n\t\t\t\t\t===========================";
        cout<< "\n  Pilihan";
        cout<< "\n--------------\n";
        cout<< "1. Insert AVL\n";
        cout<< "2. Insert BST" <<endl;
        cout<< "3. Delete AVL" <<endl;
        cout<< "4. Delete BST" <<endl;
        cout<< "5. Search" <<endl;
        cout<< "6. View" <<endl;
        cout<< "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> ("%c", pil);
        switch (pil)
        {
    	case '1':
            cout << "Masukkan Nomor Peserta: ";
            cin >> id;
            cout << "Masukkan Nama Peserta: ";
            cin >> nama;
            cout << "Masukkan Asal Kota: ";
            cin >> asalkota;
            tree = insertAVL(tree,id,nama,asalkota);
            _getch();
            break;
        case '2':
            cout << "Masukkan Nomor Peserta: ";
            cin >> id;
            cout << "Masukkan Nama Peserta: ";
            cin >> nama;
            cout << "Masukkan Asal Kota: ";
            cin >> asalkota;
            insert(&tree,id,nama,asalkota);
            _getch();
            break;
         case '3':
            cout << "Delete Data Avl : "<<endl;
            preOrder(tree);
            int hapus;
            cout <<"Input ID Peserta Yang di Hapus : " ;
            cin>>hapus;
            tree = deleteNode(tree,hapus);
            _getch();
            break;
        case '4':
            cout << "Delete Data BST : "<<endl;
            preOrder(tree);
            cout <<"Input ID Peserta Untuk dihapus : " ;
            cin>>hapus;
            tree = deleteBST(tree,hapus);
            _getch();
            break;
        case '5':
            cout << "Search : "<<endl;
            preOrder(tree);
            int cari;
            cout <<"Input ID Peserta : " ;
            cin>>cari;
            search(tree,cari);
            _getch();
            break;
        case '6':
            cout << "Data Kosong!! "<<endl;
            if (tree!=NULL)
            {
                cout << " ID  \tNama \t\tAsalkota"<<endl  ;
                cout << "---------------------------------"<<endl  ;
                preOrder(tree);
            }
            _getch();
            break;
        
        case '0':
            exit(0);
            break;
        default:
            break;
        }

    }
    
}
