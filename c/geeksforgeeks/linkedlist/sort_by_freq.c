struct BSTNode
{
  struct BSTNode * left;
  int data;
  int freq;
  struct BSTNode * right;
};


struct dataFreq
{
  int data;
  int freq;
};


int compare (const void * a, const void * b)
{
  return ((*(const dataFreq*)b).freq - (*(const dataFreq*)a).freq);
}


BSTNode * newNode (int data)
{
  struct BSTNode * node = new BSTNode;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->freq = 1;
  return (node);
}


BSTNode * insert (BSTNode * root, int data)
{
  if (root == NULL)
    return newNode (data);
  if (data == root->data)
    root->freq += 1;
  else if (data < root->data)
    root->left = insert (root->left, data);
  else
    root->right = insert (root->right, data);
  return root;
}


void store (BSTNode * root, dataFreq count[], int *index)
{
  if (root == NULL) return;

  store (root->left, count, index);

  count[(*index)].freq = root->freq;
  count[(*index)].data = root->data;
  (*index)++;

  store(root->right, count, index);
}

void sortByFrequency (int array[], int n)
{
  struct BSTNode * root = NULL;
  for (int i = 0; i < n; ++i)
    root = insert (root, array[i]);

  dataFreq count[n];
  int index = 0;
  store(root, count, &index);

  qsort(count, index, sizeof(count[0]), compare);

  int j = 0; 
  for (int i = 0; i < index; ++i)
  {
    for (int freq = count[i].freq; freq > 0; freq--)
    {
      array[j++] = count[i].data;
    }
  } 
}


void printArray(int array[], int n)
{
  for (int i = 0; i < n; ++i)
    std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main()
{
  int array[] = {2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12};
  int n = sizeof(array)/sizeof(array[0]);

  sortByFrequency(array, n);
  printArray(array, n);

  return 0;

}
