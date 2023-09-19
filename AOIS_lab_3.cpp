#include <iostream>
#include <vector>
#include <string>
//(!x1!x2!x3)V(!x1!x2x3)V(!x1x2!x3)V(x1x2!x3)
//(!x1Vx2Vx3)*(x1V!x2V!x3)*(x1V!x2Vx3)*(x1Vx2Vx3)

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> findPair(std::vector<std::vector<int>> data);
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> necessaryPair(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data);
std::vector<std::vector<int>> createQuineTable(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tableOfPair, std::vector<std::vector<int>> tableOfInput);
std::vector<int> necessryQuinePair(std::vector<std::vector<int>> data);
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> quineTNF(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data, std::vector<int> data1);
std::vector<std::vector<int>> createMapKarno(std::vector<std::vector<int>> data);
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> mapKarnoTNF(std::vector<std::vector<int>> data);
void viewPairsVector(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data, std::string simvols);

int main()
{
    bool is_not = false;
    int openedBreckets = 0;
    std::string inputSDNF, inputSKNF;
    std::vector<int> bufferVectorOfTable, vectorOfNecessaryPairSKNF, vectorOfNecessaryPairSDNF;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tableOfPairOfSDNF, tableOfPairOfSKNF, tableOfTDNF, tableOfTKNF, tableQuineTDNF, tableQuineTKNF, mapKarnoTDNF, mapKarnoTKNF;
    std::vector <std::vector<int>> tableOfSDNF, tableOfSKNF, tableQuineOfSDNF, tableQuineOfSKNF, mapKarnoSDNF, mapKarnoSKNF;
    std::cin >> inputSDNF;
    std::cin >> inputSKNF;

    for (int i = 0; i < inputSDNF.size(); i++)
    {
        if (inputSDNF.at(i) == 'V' or inputSDNF.at(i) == '1' or inputSDNF.at(i) == '2' or inputSDNF.at(i) == '3')
        {
            continue;
        }
        if (inputSDNF.at(i) == 'x')
        {
            if (is_not)
            {
                bufferVectorOfTable.push_back(0);
            }
            else
            {
                bufferVectorOfTable.push_back(1);
            }
            is_not = false;
            continue;
        }
        if (inputSDNF.at(i) == '(')
        {
            openedBreckets++;
        }
        if (inputSDNF.at(i) == ')')
        {
            openedBreckets--;
        }
        if (openedBreckets == 0)
        {
            tableOfSDNF.push_back(bufferVectorOfTable);
            bufferVectorOfTable.clear();
        }
        if (inputSDNF.at(i) == '!')
        {
            is_not = true;
        }
    }
    for (int i = 0; i < inputSKNF.size(); i++)
    {
        if (inputSKNF.at(i) == '*' or inputSKNF.at(i) == '1' or inputSKNF.at(i) == '2' or inputSKNF.at(i) == '3')
        {
            continue;
        }
        if (inputSKNF.at(i) == 'x')
        {
            if (is_not)
            {
                bufferVectorOfTable.push_back(0);
            }
            else
            {
                bufferVectorOfTable.push_back(1);
            }
            is_not = false;
            continue;
        }
        if (inputSKNF.at(i) == '(')
        {
            openedBreckets++;
        }
        if (inputSKNF.at(i) == ')')
        {
            openedBreckets--;
        }
        if (openedBreckets == 0)
        {
            tableOfSKNF.push_back(bufferVectorOfTable);
            bufferVectorOfTable.clear();
        }
        if (inputSKNF.at(i) == '!')
        {
            is_not = true;
        }
    }
    tableOfPairOfSDNF = findPair(tableOfSDNF);
    tableOfPairOfSKNF = findPair(tableOfSKNF);
    tableOfTDNF = necessaryPair(tableOfPairOfSDNF);
    tableOfTKNF = necessaryPair(tableOfPairOfSKNF);
    std::cout << "CALC" << "\n";
    viewPairsVector(tableOfTDNF, "*+");
    std::cout << "\n";
    viewPairsVector(tableOfTKNF, "+*");
    tableQuineOfSDNF = createQuineTable(tableOfPairOfSDNF, tableOfSDNF);
    tableQuineOfSKNF = createQuineTable(tableOfPairOfSKNF, tableOfSKNF);
    vectorOfNecessaryPairSDNF = necessryQuinePair(tableQuineOfSDNF);
    vectorOfNecessaryPairSKNF = necessryQuinePair(tableQuineOfSKNF);
    tableQuineTDNF = quineTNF(tableOfPairOfSDNF, vectorOfNecessaryPairSDNF);
    tableQuineTKNF = quineTNF(tableOfPairOfSKNF, vectorOfNecessaryPairSKNF);
    std::cout << "\n" << "MCCLUSKEY" << "\n";
    viewPairsVector(tableQuineTDNF, "*+");
    std::cout << "\n";
    viewPairsVector(tableQuineTKNF, "+*");
    mapKarnoSDNF = createMapKarno(tableOfSDNF);
    mapKarnoSKNF = createMapKarno(tableOfSKNF);
    mapKarnoTDNF = mapKarnoTNF(mapKarnoSDNF);
    mapKarnoTKNF = mapKarnoTNF(mapKarnoSKNF);
    std::cout << "\n" << "KARNO" << "\n";
    viewPairsVector(mapKarnoTDNF, "*+");
    std::cout << "\n";
    viewPairsVector(mapKarnoTKNF, "+*");
}

bool check(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pairs, std::pair<std::pair<int, int>, std::pair<int, int>> pair)
{
    for (int i = 0; i < pairs.size(); i++)
    {
        if (pairs.at(i) == pair) return true;
    }
    return false;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> findPair(std::vector<std::vector<int>> data)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> result;
    
    for (int i = 0; i < data.size(); i++)
    {
        bool oneTwoPairFlag = false, oneTreePairFlag = false, twoTreePairFlag = false;
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pairs, bufferResult;
        pairs.push_back(std::make_pair(std::make_pair(0, data.at(i).at(0)), std::make_pair(1, data.at(i).at(1))));
        pairs.push_back(std::make_pair(std::make_pair(0, data.at(i).at(0)), std::make_pair(2, data.at(i).at(2))));
        pairs.push_back(std::make_pair(std::make_pair(1, data.at(i).at(1)), std::make_pair(2, data.at(i).at(2))));
        if (check(result, pairs.at(0)))
        {
            oneTwoPairFlag = true;
        }
        if (check(result, pairs.at(1)))
        {
            oneTreePairFlag = true;
        }
        if (check(result, pairs.at(2)))
        {
            twoTreePairFlag = true;
        }
        for(int j = i + 1; j< data.size(); j++)
        {
            if (data.at(j).at(0) == data.at(i).at(0) and data.at(i).at(1) == data.at(j).at(1) and !oneTwoPairFlag) 
            {
                result.push_back(pairs.at(0));
            }
            if (data.at(j).at(0) == data.at(i).at(0) and data.at(i).at(2) == data.at(j).at(2) and !oneTreePairFlag)
            {
                result.push_back(pairs.at(1));
            }
            if (data.at(j).at(1) == data.at(i).at(1) and data.at(i).at(2) == data.at(j).at(2) and !twoTreePairFlag)
            {
                result.push_back(pairs.at(2));
            }
        }
        pairs.clear();
    }   
    return result;
}

bool findSamePositive(std::pair<int, int> target, std::pair<int, int> data1, std::pair<int, int> data2, std::pair<int, int> data3, std::pair<int, int> data4)
{
    bool result = false;
    if ((target.first == data1.first and target.second == data1.second) or (target.first == data2.first and target.second == data2.second))
    {
        result = true;
    }
    if ((target.first == data3.first and target.second == data3.second) or (target.first == data4.first and target.second == data4.second))
    {
        result = true;
    }
    return result;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> necessaryPair(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> result;
    bool flag = false;
    if(findSamePositive(data.at(0).first, data.at(1).first, data.at(1).second, data.at(2).first, data.at(2).second))
    {
        flag = true;
    }
    if (!flag or !findSamePositive(data.at(0).second, data.at(1).first, data.at(1).second, data.at(2).first, data.at(2).second))
    {
        result.push_back(data.at(0));
    }
    flag = false;
    if (findSamePositive(data.at(1).first, data.at(0).first, data.at(0).second, data.at(2).first, data.at(2).second))
    {
        flag = true;
    }
    if (!flag or !findSamePositive(data.at(1).second, data.at(0).first, data.at(0).second, data.at(2).first, data.at(2).second))
    {
        result.push_back(data.at(1));
    }
    flag = false;
    if (findSamePositive(data.at(2).first, data.at(0).first, data.at(0).second, data.at(1).first, data.at(1).second))
    {
        flag = true;
    }
    if (!flag or !findSamePositive(data.at(2).second, data.at(0).first, data.at(0).second, data.at(1).first, data.at(1).second))
    {
        result.push_back(data.at(2));
    }
    return result;
}

bool asd(std::pair<int, int> data1, std::vector<int> data2)
{
    if (data1.first == 0 and data1.second == data2.at(0))
    {
        return true;
    }
    if (data1.first == 1 and data1.second == data2.at(1))
    {
        return true;
    }
    if (data1.first == 2 and data1.second == data2.at(2))
    {
        return true;
    }
    return false;
}

std::vector<std::vector<int>> createQuineTable(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tableOfPair, std::vector<std::vector<int>> tableOfInput)
{
    std::vector<std::vector<int>> result;
    result.push_back({});
    result.push_back({});
    result.push_back({});
    result.push_back({});
    for (int i = 0; i < tableOfInput.size(); i++)
    {
        for(int j = 0; j < tableOfPair.size(); j++)
        {
            if (asd(tableOfPair.at(j).first, tableOfInput.at(i)) and asd(tableOfPair.at(j).second, tableOfInput.at(i)))
            {
                result.at(i).push_back(1);
            }
            else
            {
                result.at(i).push_back(0);
            }
        }
    }
    return result;
}

std::vector<int> necessryQuinePair(std::vector<std::vector<int>> data)
{
    std::vector<int> result;
    for (int i = 0; i < data.at(0).size(); i++)
    {
        result.push_back(2);
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).at(0) == data.at(i).at(1) and data.at(i).at(0) == 1 and data.at(i).at(1) == 1)
        {
            result.at(0)--;
            result.at(1)--;
        }
        if (data.at(i).at(0) == data.at(i).at(2) and data.at(i).at(0) == 1 and data.at(i).at(2) == 1)
        {
            result.at(0)--;
            result.at(2)--;
        }
        if (data.at(i).at(1) == data.at(i).at(2) and data.at(i).at(1) == 1 and data.at(i).at(2) == 1)
        {
            result.at(1)--;
            result.at(2)--;
        }
    }
    return result;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> quineTNF(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data, std::vector<int> data1)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> result;
    for (int i = 0; i < data1.size(); i++)
    {
        if(data1.at(i) == 1) 
        {
            result.push_back(data.at(i));
        }
    }
    return result;
}

int pairForMapKarno(int data1, int data2)
{
    if (data1 == 0 and data2 == 0)
    {
        return 0;
    }
    if (data1 == 0 and data2 == 1)
    {
        return 1;
    }
    if (data1 == 1 and data2 == 0)
    {
        return 2;
    }
    if (data1 == 1 and data2 == 1)
    {
        return 3;
    }
}

std::vector<std::vector<int>> createMapKarno(std::vector<std::vector<int>> data)
{   // x 00 01 10 11 (!x1!x2!x3)V(!x1!x2x3)V(!x1x2!x3)V(x1x2!x3)
    // 0 1  1  1  0                         1   1     1  ?     x  x     ?   1
    // 1 0  0  1  0  (!x1!x2)V(x2!x3)  =  (!x1V!x3)*(!x1Vx2)*(!x2Vx2)*(!x2V!x3)
    std::vector<std::vector<int>> result = { {0, 0, 0, 0}, {0, 0, 0, 0} };
    for (int i = 0; i < data.size(); i++)
    {
        if(data.at(i).at(0) == 0)
        {
            switch (pairForMapKarno(data.at(i).at(1), data.at(i).at(2)))
            {
            case 0:
                result.at(0).at(0) = 1;
                break;
            case 1:
                result.at(0).at(1) = 1;
                break;
            case 2:
                result.at(0).at(2) = 1;
                break;
            case 3:
                result.at(0).at(3) = 1;
                break;
            }
        }
        else
        {
            switch (pairForMapKarno(data.at(i).at(1), data.at(i).at(2)))
            {
            case 0:
                result.at(1).at(0) = 1;
                break;
            case 1:
                result.at(1).at(1) = 1;
                break;
            case 2:
                result.at(1).at(2) = 1;
                break;
            case 3:
                result.at(1).at(3) = 1;
                break;
            }
        }
    }
    return result;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> mapKarnoTNF(std::vector<std::vector<int>> data)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> finalResult;
    std::pair<std::pair<int, int>, std::pair<int, int>> bufferPair;
    for (int i = 0; i < 4; i++)
    {
        if (data.at(0).at(i) == 1 and data.at(1).at(i) == 1)
        {
            switch (i) 
            {
            case 0:
                bufferPair.first.first = 1;
                bufferPair.first.second = 0;
                bufferPair.second.first = 2;
                bufferPair.second.second = 0;
                data.at(0).at(i) = 0;
                data.at(1).at(i) = 0;
                break;
            case 1:
                bufferPair.first.first = 1;
                bufferPair.first.second = 0;
                bufferPair.second.first = 2;
                bufferPair.second.second = 1;
                data.at(0).at(i) = 0;
                data.at(1).at(i) = 0;
                break;
            case 2:
                bufferPair.first.first = 1;
                bufferPair.first.second = 1;
                bufferPair.second.first = 2;
                bufferPair.second.second = 0;
                data.at(0).at(i) = 0;
                data.at(1).at(i) = 0;
                break;
            case 3:
                bufferPair.first.first = 1;
                bufferPair.first.second = 1;
                bufferPair.second.first = 2;
                bufferPair.second.second = 1;
                data.at(0).at(i) = 0;
                data.at(1).at(i) = 0;
                break;
            }
            finalResult.push_back(bufferPair);
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (data.at(0).at(i) == 1 and data.at(0).at(i + 1) == 1)
        {
            switch (i)
            {
            case 0:
                bufferPair.first.first = 0;
                bufferPair.first.second = 0;
                bufferPair.second.first = 1;
                bufferPair.second.second = 0;
                break;
            case 2:
                bufferPair.first.first = 0;
                bufferPair.first.second = 0;
                bufferPair.second.first = 1;
                bufferPair.second.second = 1;
                break;
            }
            finalResult.push_back(bufferPair);
            break;
        }
        if (data.at(1).at(i) == 1 and data.at(1).at(i + 1) == 1)
        {
            switch (i)
            {
            case 0:
                bufferPair.first.first = 0;
                bufferPair.first.second = 1;
                bufferPair.second.first = 1;
                bufferPair.second.second = 0;
                break;
            case 2:
                bufferPair.first.first = 0;
                bufferPair.first.second = 1;
                bufferPair.second.first = 1;
                bufferPair.second.second = 1;
                break;
            }
            finalResult.push_back(bufferPair);
            break;
        }
    }
    return finalResult;
}


void viewPairsVector(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data, std::string simvols)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).first.second == 0)
        {
            std::cout << "!";
        }
        std::cout << "x" << data.at(i).first.first + 1 << simvols.at(0);
        if (data.at(i).second.second == 0)
        {
            std::cout << "!";
        }
        std::cout << "x" << data.at(i).second.first + 1;
        if(i != data.size() - 1)
        {
            std::cout << " " << simvols.at(1) << " ";
        }
    }
}


