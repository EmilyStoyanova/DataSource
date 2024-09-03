#include"DataSource.hpp"
#include"ArrayDataSource.hpp"
#include"DefaultDataSource.hpp"
#include"FileDataSource.hpp"
#include"AlternateDataSource.hpp"
#include"GeneratorDataSource.hpp"
#include"Vector.hpp"
#include<cstdlib>
#include <iostream>
#include <stdexcept> 

const int CURRENT_SIZE = 1000;
const int NUMBER_OF_LETTERS = 26;
const int LENGTH = 10;
const int MAX_LENGTH = 100;
const int N = 25;

int nextPrime() {
    static int last = 1;
    while (true) {
        ++last;
        bool isPrime = true;
        for (int i = 2; i <= std::sqrt(last); ++i) {
            if (last % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) return last;
    }
}

int generateRandomNumber() {
    return std::rand() % 1000;
}

int* fibonacci(int n) {   
    if (n <= 0) {
        return nullptr;
    }

    int* array = new int[n];

    if (n == 1) {
        array[0] = 0;
    }
    else if (n >= 2) {
        array[0] = 0;
        array[1] = 1;
        for (int i = 2; i < n; ++i) {
            array[i] = array[i - 1] + array[i - 2];
        }
    }

    return array;
}

char* generateRandomString(int n) {
    char* str = new char[n+1];
    for (int i = 0; i < n; ++i) {
        str[i] = static_cast<char>('a' + std::rand() % NUMBER_OF_LETTERS);
    }
    str[n] = '\0';
    return str;
}
int main()
{ 
    
    try { 

        std::cout << "First subtask: " << std::endl;
        char* strings[N];
        for (int i = 0; i < N; ++i) {
              strings[i] = generateRandomString(LENGTH);
         }
        ArrayDataSource<char*> dataSource(strings, N);
        while (dataSource.hasNext()) {
            const char* randomString = dataSource.nextElement();
            if (randomString) {
                 std::cout << randomString << std::endl;
             }
        }
        for (int i = 0; i < N; ++i) {
            delete[] strings[i]; 
        }

        std::cout << std::endl;
        std::cout << "Second subtask: " << std::endl;
        GeneratorDataSource<int> primeSource(nextPrime);
        GeneratorDataSource<int> randomSource(generateRandomNumber);
        int* fibonacciNumbers = fibonacci(N);
        ArrayDataSource<int> fibonacciSource(fibonacciNumbers, N);

        Vector<DataSource<int>*> sources;
        sources.push_back(&primeSource);
        sources.push_back(&randomSource);
        sources.push_back(&fibonacciSource);
        AlternateDataSource<int> alternateSource(sources);


        Vector<int> numbers(CURRENT_SIZE);
        for (size_t i = 0; i < numbers.getSize(); ++i) {
            numbers[i] = alternateSource.nextElement();
        }

        char fileName[MAX_LENGTH];
        std::cout << "Enter the name of the binary file (with .bin extension): ";
        std::cin >> fileName;
        std::ofstream binFile(fileName, std::ios::binary);
        if (!binFile) {
            throw std::runtime_error("Cannot open binary file for writing");
        }
        binFile.write(reinterpret_cast<const char*>(numbers.getData()), numbers.getSize() * sizeof(int));
        binFile.close();


        std::ifstream binFileIn(fileName, std::ios::binary);
        if (!binFileIn) {
            throw std::runtime_error("Cannot open binary file for reading");
        }

        std::ofstream tåxtFile("numbers.txt");
        if (!tåxtFile) {
            throw std::runtime_error("Cannot open text file for writing");
        }

        int value;
        while (binFileIn.read(reinterpret_cast<char*>(&value), sizeof(int))) {
            tåxtFile << value << std::endl;
        }
        binFileIn.close();
        tåxtFile.close();

        FileDataSource<int> fileSource("numbers.txt");
        while (fileSource) {
            std::cout << fileSource() << std::endl;
        }

        delete[] fibonacciNumbers;

    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "An unknown exception has occurred!" <<std::endl;
    }

    /*int array[] = {1, 2, 3, 4, 5};

    ArrayDataSource<int> dataSource(array,5);

    while (dataSource.hasNext()) {
        std::cout << dataSource.nextElement() << " ";
    }
    std::cout << std::endl;

    dataSource = dataSource + 6;
    while (dataSource.hasNext()) {
        std::cout << dataSource.nextElement() << " ";
    }
    std::cout << std::endl;

    dataSource += 7;
    while (dataSource.hasNext()) {
        std::cout << dataSource.nextElement() << " ";
    }
    std::cout << std::endl;

    dataSource.reset();
    while (dataSource.hasNext()) {
        std::cout << dataSource.nextElement() << " ";
    }
    std::cout << std::endl;

    dataSource.reset();
    std::cout << dataSource.nextElement() << std::endl;
    dataSource.nextElements(6).print(std::cout);
    --dataSource;  
    dataSource.nextElements(1).print(std::cout);
    

    dataSource.reset();
    dataSource.nextElements(7).print(std::cout);
    */

    /*DefaultDataSource<int> data;
    /*while (data.hasNext()) {
        std::cout << data.nextElement() << " ";
    }
    data.nextElements(10).print(std::cout);
    std::cout<<data.hasNext();
    */ 

    /*FileDataSource<int> fileSource("data.txt");
        while (fileSource) {
            int value;
            //int nextValue;
            fileSource >> value;
        }
        
        fileSource.reset();
        //fileSource.nextElements(2).print(std::cout);
        fileSource.nextElements(4).print(std::cout);
        //fileSource.nextElements(10).print(std::cout);
        std::cout << fileSource.hasNext() << std::endl;
        fileSource.reset();
        std::cout << fileSource.hasNext() << std::endl;
        */

    /*int array1[] = {1,2,3};
    ArrayDataSource<int> d1(array1, 3);
    int array2[] = {4 };
    ArrayDataSource<int> d2(array2, 1);
    
    Vector<DataSource<int>*> dataSources;
    dataSources.push_back(&d1);
    dataSources.push_back(&d2);

    AlternateDataSource<int> obj (dataSources);

    while (obj.hasNext()) {
        std::cout << obj.nextElement() << std::endl;
    }
    obj.reset();
    while (obj.hasNext()) {
        std::cout << obj.nextElement() << std::endl;
    }
    std::cout<<obj.hasNext() << std::endl;
    obj.reset();
    std::cout << obj.hasNext() << std::endl;
    int value1, value2;
    while (obj.hasNext()) {
        obj >> value1 >> value2;
        std::cout << value1 << " " << value2 << std::endl;
    }
    obj.reset();
    std::cout << obj.nextElement() << std::endl;
    obj.nextElements(3).print(std::cout);
    obj.reset();
    std::cout << "Testing operator()" << std::endl;
    while (obj.hasNext()) {
        int value = obj();  
        std::cout << value << std::endl;
    }
    std::cout << "Testing operator bool" << std::endl;
    if (!obj) {
        std::cout << "No more elements." << std::endl;
    }


    obj.reset();///
    while (obj) {  // operator bool
        int value = obj();  // operator ()
        std::cout << value << std::endl;
    }
    obj.reset();///
    int value1, value2, value3;
    while (obj.hasNext()) {
        obj >> value1>>value2>>value3;
        std::cout << value1<<" "<<value2<<" " << value3 << std::endl;
    }

    */

    /*int array1[] = {1,2,3};
    ArrayDataSource<int> d1(array1, 3);
    FileDataSource<int> d2("text.txt");

    Vector<DataSource<int>*> dataSources;
    dataSources.push_back(&d1);
    dataSources.push_back(&d2);

    AlternateDataSource<int> obj(dataSources);

    while (obj.hasNext()) {
        std::cout << obj.nextElement() << std::endl;
    }
    std::cout <<"Is there a next one? " <<obj.hasNext() << std::endl;
    obj.reset();
    while (obj.hasNext()) {
        std::cout << obj.nextElement() << std::endl;
    }
    std::cout << std::endl;
    obj.reset();
    while (obj) {  // operator bool
        int value = obj();  // operator ()
        std::cout << value << std::endl;
    }
    obj.reset();
    std::cout << obj.hasNext() << std::endl;
    int value1, value2;
    while (obj.hasNext()) {
         obj >> value1>>value2 ;
         std::cout << value1 << " " << value2 << std::endl;
}
*/
    
    return 0;
}

