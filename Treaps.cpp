#include <iostream>
#include <ctime>

struct TreapNode
{
    int data, oncelik;
    TreapNode *sol, *sag;
};

TreapNode *sagRotate(TreapNode *y)
{
    TreapNode *x = y->sol,  *T2 = x->sag;

    x->sag = y;
    y->sol = T2;
    return x;
}

TreapNode *solRotate(TreapNode *x)
{
    TreapNode *y = x->sag, *T2 = y->sol;

    y->sol = x;
    x->sag = T2;

    return y;
}

TreapNode* newNode(int deger)
{
    TreapNode* temp = new TreapNode;
    temp->data = deger;
    temp->oncelik = rand()%100;
    temp->sol = temp->sag = NULL;
    return temp;
}

void arama(TreapNode *root,int deger)
{
  TreapNode *temp = root;
  bool found = false;
  while(temp != NULL)
  {
      if(deger == temp->data)
      {
          found = true;
          break;
      }
      else
      {
          if(deger < temp->data)
            temp = temp->sol;
          else
            temp = temp->sag;

      }
  }
  if(found)
  {
      std::cout << deger <<  " bulundu" << std::endl;
  }
  else
  {
      std::cout << deger << " bulunamadi" << std::endl;
  }

}

TreapNode* ekleme(TreapNode* root, int deger)
{
    if (!root)
        return newNode(deger);

    if (deger <= root->data)
    {
        root->sol = ekleme(root->sol, deger);

        if (root->sol->oncelik > root->oncelik)
            root = sagRotate(root);
    }
    else
    {
        root->sag = ekleme(root->sag, deger);

        if (root->sag->oncelik > root->oncelik)
            root = solRotate(root);
    }
    return root;
}
 

TreapNode* silmeNode(TreapNode* root, int deger)
{
    if (root == NULL)
        return root;
 
    if (deger < root->data)
        root->sol = silmeNode(root->sol, deger);
    else if (deger > root->data)
        root->sag = silmeNode(root->sag, deger);

    else if (root->sol == NULL)
    {
        TreapNode *temp = root->sag;
        delete(root);
        root = temp;
    }
 
    else if (root->sag == NULL)
    {
        TreapNode *temp = root->sol;
        delete(root);
        root = temp;
    }
 
    else if (root->sol->oncelik < root->sag->oncelik)
    {
        root = solRotate(root);
        root->sol = silmeNode(root->sol, deger);
    }
    else
    {
        root = sagRotate(root);
        root->sag = silmeNode(root->sag, deger);
    }
 
    return root;
}
 
void inorder(TreapNode* root)
{
    if (root)
    {
        inorder(root->sol);
        std:: cout << "deger: "<< root->data << " | oncelik: "
            << root->oncelik;
        if (root->sol)
            std::cout << " | sol cocuk: " << root->sol->data;
        if (root->sag)
            std::cout << " | sag cocuk: " << root->sag->data;
        std::cout << std::endl;
        inorder(root->sag);
    }
}
 
 void printArray(int array[30])
{
    for(int i = 0; i < 30; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    srand(time(NULL));
    struct TreapNode *root = NULL;

    int array[30];

    for(auto& iter:array)
    {
        iter = rand() + 1;
    }

   // printArray(array);

    for(int i = 0; i < 30; i++)
    {
        root = ekleme(root,array[i]);
    }

    inorder(root);

    silmeNode(root,array[5]);

    inorder(root);

    return 0;
}