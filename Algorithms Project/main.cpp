#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <sstream>
#include <fstream>
#include <algorithm>
// #include <bits/stdc++.h>
using namespace std;
using namespace ::chrono;

void home();
void readRecord();
void bigData();

struct Record
{
    int index;
    string organization_Id;
    string name;
    string website;
    string country;
    string description;
    int founded;
    string industry;
    int no_of_employees;
};

vector<Record> v;

void insert(Record company)
{
    v.push_back(company);
}
void printEmployeeIndexes()
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].no_of_employees << "\t";
    }
}
void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//////////////////Bubble Sort////////////////
void bubbleSort() // class ki waja sa ham na function ko parameters pass ni kiya.
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        bool isSwapped = false;
        for (int j = 0; j < v.size() - 1 - i; j++)
        {
            if (v[j].no_of_employees > v[j + 1].no_of_employees)
            {
                swap(v[j], v[j + 1]);
                isSwapped = true;
            }
        }

        // In case if the vector list is already sorted
        if (isSwapped == false)
        {
            break;
        }
    }
}
//////////////////Insertion Sort////////////////
void insertionSort()
{
    Record temp;

    for (int x = 1; x < v.size(); x++)
    {
        temp = v[x];
        int y = x - 1;
        while (y >= 0 && temp.no_of_employees < v[y - 1].no_of_employees) // asending order.
        {
            v[y].no_of_employees = v[y - 1].no_of_employees;
            y--;
        }
        v[y].no_of_employees = temp.no_of_employees;
    }
}
//////////////////Selection Sort////////////////
void selectionSort()
{
    int minIdx;
    for (int i = 0; i < v.size() - 1; i++)
    {
        Record min = v[i];
        minIdx = i;
        for (int j = i; j < v.size(); j++)
        {
            if (v[minIdx].no_of_employees > v[j].no_of_employees)
            {
                minIdx = j;
                min = v[j];
            }
        }
        swap(v[i], v[minIdx]);
    }
}

//////////////////Merge Sort////////////////

void merge(vector<Record> &DataBase, int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    queue<Record> tempData;
    while (i <= mid && j <= end)
    {
        if (DataBase[i].no_of_employees < DataBase[j].no_of_employees)
        {
            tempData.push(DataBase[i]);
            i++;
        }
        else
        {
            tempData.push(DataBase[j]);
            j++;
        }
    }
    while (i <= mid)
    {
        tempData.push(DataBase[i]);
        i++;
    }
    while (j <= end)
    {
        tempData.push(DataBase[j]);
        j++;
    }
    for (int x = start; x <= end; x++)
    {
        DataBase[x] = tempData.front();
        tempData.pop();
    }
}

void mergeSort(vector<Record> &DataBase, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(DataBase, start, mid);
        mergeSort(DataBase, mid + 1, end);
        merge(DataBase, start, mid, end);
    }
}

//////////////////Quick Sort////////////////


// last element is taken as pivot

// static int partition(int startIndex, int endIndex)
// {
//     int pivotIndex = (startIndex + endIndex) / 2;
//     int pivotValue = v[pivotIndex].no_of_employees;

//     while (true)
//     {
//         // start at the FIRST index of the sub-arr and increment
//         // FORWARD until we find a value that is > pivotValue
//         while (v[startIndex].no_of_employees < pivotValue)
//         {
//             startIndex++;
//         }

//         // start at the LAST index of the sub-arr and increment
//         // BACKWARD until we find a value that is < pivotValue
//         while (v[endIndex].no_of_employees > pivotValue)
//         {
//             endIndex--;
//         }

//         if (startIndex >= endIndex)
//         {
//             return endIndex;
//         }

//         // swap values at the startIndex and endIndex
//         int temp = v[startIndex].no_of_employees;
//         v[startIndex] = v[endIndex];
//         v[endIndex].no_of_employees = temp;
//         // swap(v[startIndex].no_of_employees,v[endIndex].no_of_employees);
//     }
// }

// void quickSort(int startIndex, int endIndex)
// {
//     // verify that the start and end index have not overlapped
//     if (startIndex < endIndex)
//     {
//         // calculate the pivotIndex
//         int pivotIndex = partition(startIndex, endIndex);
//         // sort the left sub-arr
//         quickSort(startIndex, pivotIndex);
//         // sort the right sub-arr
//         quickSort(pivotIndex + 1, endIndex);
//     }
// }

int partition(vector<Record> &arr, int start, int end)
{
 
    int pivot = arr[start].no_of_employees;
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i].no_of_employees <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i].no_of_employees <= pivot) {
            i++;
        }
 
        while (arr[j].no_of_employees > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(vector<Record>&arr, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}



//////////////////Heap Sort////////////////

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(vector<Record> &v, int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && v[l].no_of_employees > v[largest].no_of_employees)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && v[r].no_of_employees > v[largest].no_of_employees)
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(v[i], v[largest]);

        // Recursively heapify the affected sub-tree
        heapify(v, n, largest);
    }
}
// main function to do heap sort
void heapSort(vector<Record> &v, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(v[0], v[i]);

        // call max heapify on the reduced heap
        heapify(v, i, 0);
    }
}

////////////////Count Sort/////////////

void countingSort(vector<Record> &arr)
{
    // Record max = *max_element(arr.begin(), arr.end());
    int max = arr[0].no_of_employees;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].no_of_employees > max)
        {
            max = arr[i].no_of_employees;
        }
    }
    vector<Record> count(max + 1);
    vector<Record> output(arr.size());
    for (int x = 0; x < arr.size(); x++)
    {
        count[arr[x].no_of_employees].no_of_employees++;
    }
    for (int x = 1; x < count.size(); x++)
    {
        count[x].no_of_employees = count[x - 1].no_of_employees + count[x].no_of_employees;
    }
    for (int x = arr.size() - 1; x >= 0; x--)
    {
        int index = count[arr[x].no_of_employees].no_of_employees - 1;
        count[arr[x].no_of_employees].no_of_employees--;
        output[index] = arr[x];
    }
    for (int x = 0; x < output.size(); x++)
    {
        arr[x] = output[x];
    }
}

///////////////Raddix Sort/////////////

void Raddix(vector<Record> &arr, int place)

{
    vector<int> count(100);
    vector<int> output(arr.size());
    for (int x = 0; x < arr.size(); x++)
    {
        count[(arr[x].no_of_employees / place) % 10]++;
    }
    for (int x = 1; x < count.size(); x++)
    {
        count[x] = count[x - 1] + count[x];
    }
    for (int x = arr.size() - 1; x >= 0; x--)
    {
        int index = count[(arr[x].no_of_employees / place) % 10] - 1;
        count[(arr[x].no_of_employees / place) % 10]--;
        output[index] = arr[x].no_of_employees;
    }
    for (int x = 0; x < output.size(); x++)
    {
        arr[x].no_of_employees = output[x];
    }
}

void countingSort(vector<Record> &arr, int place)

{
    vector<Record> count(10);
    vector<Record> output(arr.size());
    for (int x = 0; x < arr.size(); x++)
    {
        count[(arr[x].no_of_employees / place) % 10].no_of_employees++;
    }
    for (int x = 1; x < count.size(); x++)
    {
        count[x].no_of_employees = count[x - 1].no_of_employees + count[x].no_of_employees;
    }
    for (int x = arr.size() - 1; x >= 0; x--)
    {
        int index = count[(arr[x].no_of_employees / place) % 10].no_of_employees - 1;
        count[(arr[x].no_of_employees / place) % 10].no_of_employees--;
        output[index] = arr[x];
    }
    for (int x = 0; x < output.size(); x++)
    {
        arr[x] = output[x];
    }
}

void radixSort(vector<Record> &arr)
{
    // Record max = *max_element(arr.begin(), arr.end());
    int max = arr[0].no_of_employees;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].no_of_employees > max)
        {
            max = arr[i].no_of_employees;
        }
    }
    int place = 1;
    while ((max / place) > 0)
    {
        countingSort(arr, place);
        place = place * 10;
    }
}

////////////////Buckket Sort////////////

int getMax(vector<Record> &a, int n) // function to get maximum element from the given array
{
    int max = a[0].no_of_employees;
    for (int i = 1; i < n; i++)
        if (a[i].no_of_employees > max)
            max = a[i].no_of_employees;
    return max;
}
void bucketSort(vector<Record> &a , int n) // function to implement bucket sort
{
    int max = getMax(a, n); // max is the maximum element of array
    int bucket[max], i;
    for (int i = 0; i <= max; i++)
    {
        bucket[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        bucket[a[i].no_of_employees]++;
    }
    for (int i = 0, j = 0; i <= max; i++)
    {
        while (bucket[i] > 0)
        {
            a[j++].no_of_employees = i;
            bucket[i]--;
        }
    }
}

string parseRecord(string line, int index)
{
    string temp = "";
    int count = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            count++;
        }
        else if (count == index)
        {
            temp += line[i];
        }
    }
    return temp;
}

bool readRecord(int index)
{
    string record = "";
    fstream file;

    if (index == 100)
    {
        file.open("organizations-100.csv", ios ::in);
    }
    else if (index == 1000)
    {
        file.open("organizations-1000.csv", ios ::in);
    }
    else if (index == 10000)
    {
        file.open("organizations-10000.csv", ios ::in);
    }
    else if (index == 100000)
    {
        file.open("organizations-100000.csv", ios ::in);
    }
    else if (index == 500000)
    {
        file.open("organizations-500000.csv", ios ::in);
    }
    else
    {
        cout << "wrong input.";
    }

    int counter = 0;
    Record rec;

    while (!file.eof())
    {
        getline(file, record);

        if (counter == 0) // to skip first line of file.
        {
            counter++;
            continue;
        }
        if (counter != 0)
        {
            int var = 0;
            stringstream(parseRecord(record, 0)) >> var;
            rec.index = var;
            rec.organization_Id = parseRecord(record, 1);
            rec.name = parseRecord(record, 2);
            rec.website = parseRecord(record, 3);
            rec.country = parseRecord(record, 4);
            rec.description = parseRecord(record, 5);
            stringstream(parseRecord(record, 6)) >> var;
            rec.founded = var;
            rec.industry = parseRecord(record, 7);
            stringstream(parseRecord(record, 8)) >> var;
            rec.no_of_employees = var;
        }
        counter++;
        insert(rec);
    }
    cout << index << "  Records added successfully.";
    file.close();
    return true;
}

////////////////////////////////////////////////////////////////////////
int main()
{
    // DataBase b;

    // vector<Record> v;
    // vector<int> vac;

    while (true)
    {
        // Record rec;
        system("cls");
    xy:
        bigData();
        char option;
        cout << "\nenter your option: ";
        cin >> option;

        if (option == '1') // 100 records
        {
        a:
            system("cls");
            readRecord(100);
            home();
            // inner options
            char op;
            cout << "\nenter your option...";
            cin >> op;

            if (op == '1')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bubbleSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '2')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                insertionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '3')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                selectionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '4')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                mergeSort(v, 0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '5')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                quickSort(v,0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '6')
            {
                cout << "Testing heap sort start" << endl;
                system("cls");
                auto start = high_resolution_clock::now();
                heapSort(v, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '7')
            {
                // cout << "Testing heap sort start" << endl;
                system("cls");
                auto start = high_resolution_clock::now();
                countingSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '8')
            {
                // cout << "Testing heap sort start" << endl;
                system("cls");
                auto start = high_resolution_clock::now();
                radixSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '9')
            {
                system("cls");

                auto start = high_resolution_clock::now();
                bucketSort(v,v.size());
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else
            {
                // cout << "wrong input" << endl;
                cout << "press any key to go back...";
                getch();
                goto a;
            }
        }
        else if (option == '2') // 1000 records
        {
        b:
            system("cls");
            readRecord(1000);
            home();
            // inner options
            char op;
            cout << "\nenter your option...";
            cin >> op;

            if (op == '1')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bubbleSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '2')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                insertionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '3')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                selectionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '4')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                mergeSort(v, 0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '5')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                quickSort(v,0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '6')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                heapSort(v, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '7')
            {
                // cout << "Testing heap sort start" << endl;
                system("cls");
                auto start = high_resolution_clock::now();
                countingSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '8')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                radixSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '9')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bucketSort(v,v.size()-1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else
            {
                // cout << "wrong input" << endl;
                cout << "press any key to go back...";
                getch();
                goto b;
            }
        }
        else if (option == '3') //  10000 records
        {
        c:
            system("cls");
            readRecord(10000);
            home();
            // inner options
            char op;
            cout << "\nenter your option...";
            cin >> op;

            if (op == '1')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bubbleSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '2')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                insertionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '3')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                selectionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '4')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                mergeSort(v, 0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '5')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                quickSort(v,0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '6')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                heapSort(v, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '7')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                countingSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '8')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                radixSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '9')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bucketSort(v,v.size()-1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else
            {
                // cout << "wrong input" << endl;
                cout << "press any key to go back...";
                getch();
                goto c;
            }
        }
        else if (option == '4') // for 100000 records
        {
        d:
            system("cls");
            readRecord(100000);
            home();
            // inner options
            char op;
            cout << "\nenter your option...";
            cin >> op;

            if (op == '1')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bubbleSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '2')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                insertionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '3')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                selectionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '4')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                mergeSort(v, 0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '5')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                quickSort(v,0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '6')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                heapSort(v, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '7')
            {
                // cout << "Testing heap sort start" << endl;
                system("cls");
                auto start = high_resolution_clock::now();
                countingSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '8')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                radixSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '9')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bucketSort(v,v.size()-1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else
            {
                // cout << "wrong input" << endl;
                cout << "press any key to go back...";
                getch();
                goto d;
            }
        }
        else if (option == '5') // 500000 records
        {
        e:
            system("cls");
            readRecord(500000);
            home();
            // inner options
            char op;
            cout << "\nenter your option...";
            cin >> op;

            if (op == '1')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bubbleSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '2')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                insertionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '3')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                selectionSort();
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '4')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                mergeSort(v, 0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '5')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                quickSort(v,0, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '6')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                heapSort(v, v.size() - 1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '7')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                countingSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '8')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                radixSort(v);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else if (op == '9')
            {
                system("cls");
                auto start = high_resolution_clock::now();
                bucketSort(v,v.size()-1);
                auto stop = high_resolution_clock::now();
                printEmployeeIndexes();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n\nTime taken by function: "
                     << duration.count() << " microseconds" << endl;

                getch();
                cout << "Press any key to continue" << endl;
                char temp;
                cin >> temp;
            }
            else
            {
                // cout << "wrong input" << endl;
                cout << "press any key to go back...";
                getch();
                goto e;
            }
        }

        else
        {
            cout << "wrong input\n";
            cout << "press any key to continue\n";
            getch();
            goto xy;
        }
    }
}

void home()
{
    cout << "\n==========================";
    cout << "\n   Sorting Algorithms";
    cout << "\n1.Bubble Sort";
    cout << "\n2.Insertion Sort";
    cout << "\n3.Selection Sort";
    cout << "\n4.Merge Sort";
    cout << "\n5.Quick Sort";
    cout << "\n6.Heap Sort";
    cout << "\n7.Count Sort";
    cout << "\n8.Raddix Sort";
    cout << "\n9.Bucket Sort";
}

void bigData()
{
    cout << "\n1.Load 100 records" << endl;
    cout << "2.Load 1000 records" << endl;
    cout << "3.Load 10000 records" << endl;
    cout << "4.Load 100000 records" << endl;
    cout << "5.Load 500000 records" << endl;
    cout << "6.Back" << endl;
}