#include <iostream>
#include <cmath>
using namespace std;

constexpr int N = 100;

int main()
{
    setlocale(LC_ALL, "Russian");
    int A, K;//количество альтернатив и критериев
    int Data[N][N];//массив с исходными данными
    cout << "Введите количество альтернатив " << endl;
    cin >> A;
    cout << "Введите количество критериев " << endl;
    cin >> K;
    cout << "Введите исходные данные" << endl;
    for (int i = 0; i < K; i++)//ввод исходных данных
    {
        for (int j = 0; j < A; j++)
        {
            cout << "Введите значения альтернатив по " << i + 1 << " критерию: ";
            cin >> Data[i][j];
        }
    }
    cout << endl;
    cout << "Исходные данные" << endl;
    for (int i = 0; i < A; ++i)//вывод заголовка альтернатив
    {
        cout.width(5);
        cout << "A" << i + 1;
    }
    cout << endl;

    for (int i = 0; i < K; ++i)//вывод заголовка критериев и данных по строкам
    {
        cout << "K" << i + 1;
        for (int j = 0; j < A; ++j)
        {
            cout.width(5);
            cout << Data[i][j];
        }
        cout << endl;
    }
    //таблица с оценками экспертов
    int ex;
    double Rates[N][N];
    cout << "Введите число экспертов" << endl;
    cin >> ex;
    cout << "Введите оценки экспертов" << endl;
    for (int i = 0; i < K; i++)//ввод оценок экспертов
    {
        for (int j = 0; j < ex; j++)
        {
            cout << "Введите значения оценок по " << i + 1 << " критерию: ";
            cin >> Rates[i][j];
        }
    }   
    cout << "Оценки экспертов" << endl;
    for (int i = 0; i < K; ++i)//вывод заголовка критериев
    {
        cout.width(5);
        cout << "K" << i + 1;
    }
    cout << endl;
    
    for (int j = 0; j < ex; ++j)//вывод заголовка критериев и оценок по строкам
    {
        cout << "Э" << j + 1;
        for (int i = 0; i < K; ++i)
        {
            cout.width(5);
            cout << Rates[i][j];
        }
        cout << endl;
    }
    //подсчет весов критериев
    double Sum, SumKr;
    Sum = 0;
    SumKr = 0;
    
    for (int i = 0;i < ex;++i)// сумма всех оценок
    {
        for (int j = 0;j < K;++j)
        {
            Sum += Rates[j][i]; 
        }
    }    
    double wages[N];
    double wage[N]; 
    cout << "Веса критериев:" << endl;
    for (int i = 0; i < K; ++i)//вывод заголовка критериев
    {
        cout.width(5);
        cout << "K" << i + 1;
    }
    cout << endl;
    
    for (int j = 0; j < K; j++)//веса критериев
    {
        wages[j] = 0;
        wage[j] = 0; 
        for (int i = 0; i < ex; i++)
        {
            wages[j] += Rates[j][i];
        }
        wage[j] = wages[j] / Sum;
        cout.width(3);
        cout << fixed;
        cout.precision(2);
        cout << " " << wage[j];
    }
    cout << endl;
    //приведение оценок альтернатив к безразмерному виду
    double max[N];
    double NonDimensional[N][N];
    int maximum;
    for (int i = 0; i < K; i++)
    {
        maximum = Data[i][0];
        for (int j = 0; j < A; j++)
        {
            if (Data[i][j] > maximum)
            {
                maximum = Data[i][j];
            }
            max[i] = maximum;
            for (int i = 0; i < K; i++)
            {
                NonDimensional[i][j] = Data[i][j] / max[i];
            }
            
        }
    }
    cout << "Оценки альтернатив в безразмерном виде:" << endl;
    for (int i = 0; i < A; ++i)//вывод заголовка критериев
    {
        cout.width(5);
        cout << "A" << i + 1;
    }
    cout << endl;

    for (int i = 0; i < K; ++i)//вывод заголовка критериев и оценок по строкам
    {
        cout << "K" << i + 1;
        for (int j = 0; j < A; ++j)
        {
            cout.width(5);
            cout << round(NonDimensional[i][j]*100)/100;
        }
        cout << endl;
    }
    //индексы согласия
    double positive = 0;
    double indexPositive[N][N];//матрица индексов согласия
    int p = 1;
    int d = 0;
    cout << "Индексы согласия:";
    for (int j = 0; j < A - 1; j++)//сравнение в прямом порядке для матрицы индексов согласия
    {
        for (int p = 1; p < A - d; p++)
        {
            for (int i = 0; i < K; i++)
            {
                if (NonDimensional[i][j] > NonDimensional[i][j + p])
                    positive = positive + wage[i];
            }
            indexPositive[j][j+p] = positive;
            positive = 0;
        }
        d = d + 1;
    }
    cout << endl;
    positive = 0;
    d = 0;
    for (int j = A - 1; j > 0; j--)//сравнение в обратном порядке для матрицы индексов согласия
    {
        for (int p = 1; p < A - d; p++)
        {
            for (int i = 0; i < K; i++)
            {
                if (NonDimensional[i][j] > NonDimensional[i][j - p])
                    positive = positive + wage[i];
            }
            indexPositive[j][j - p] = positive;
            positive = 0;
        }
        d = d + 1;
    }
    for (int i = 0; i < A; ++i)
    {
        for (int j = 0; j < A; ++j)
        {
            if (i == j)
                indexPositive[i][j] = 1;
        }
    }
    for (int i = 0; i < A; ++i)
    {
        cout.width(6);
        cout << "A" << i + 1;
    }
    cout << endl;
    for (int i = 0; i < A; ++i)
    {
        cout << "A" << i + 1;
        for (int j = 0; j < A; ++j)
        {
            cout.width(7);
            cout << fixed;
            cout.precision(2);
            cout << indexPositive[i][j];
        }
        cout << endl;
    }
    //индексы несогласия
    cout << "Индексы несогласия" << endl;;
    double negative = 0;
    d = 0;
    double maxim;
    maxim = 0; 
    double indexNegative[N][N];//матрица индексов несогласия
    for (int j = 0; j < A - 1; j++)
    {
        for (int p = 1; p < A - d; p++)
        {
            for (int i = 0; i < K; i++)
            {
                if (NonDimensional[i][j] < NonDimensional[i][j + p])
                {
                    if (NonDimensional[i][j + p] - NonDimensional[i][j] > maxim)
                    {
                        maxim = NonDimensional[i][j + p] - NonDimensional[i][j];
                    }
                }
                negative = maxim;
            }
            maxim = 0;
            indexNegative[j][j + p] = negative;
            negative = 0;
        }
        d = d + 1;
    }
    negative = 0;
    d = 0;
    maxim = 0;
    for (int j = A - 1; j > 0; j--)
    {
        for (int p = 1; p < A - d; p++)
        {
            for (int i = 0; i < K; i++)
            {
                if (NonDimensional[i][j] < NonDimensional[i][j - p])
                {
                    if (NonDimensional[i][j - p] - NonDimensional[i][j] > maxim)
                    {
                        maxim = NonDimensional[i][j - p] - NonDimensional[i][j];
                    }
                }
                negative = maxim;
            }
            maxim = 0;
            indexNegative[j][j - p] = negative;
            negative = 0;
        }
        d = d + 1;
    }
    for (int i = 0; i < A; ++i)
    {
        for (int j = 0; j < A; ++j)
        {
            if (i == j)
                indexNegative[i][j] = 0;
        }
    }
    for (int i = 0; i < A; ++i)
    {
        cout.width(6);
        cout << "A" << i + 1;
    }
    cout << endl;
    for (int i = 0; i < A; ++i)
    {
        cout << "A" << i + 1;
        for (int j = 0; j < A; ++j)
        {
            cout.width(7);
            cout << fixed;
            cout.precision(2);
            cout << indexNegative[i][j];
        }
        cout << endl;
    }
    //минимум среди строк в индексе согласия
    double minPositive[N];
    double minp;
    for (int i = 0; i < A; ++i)
    {
        minp = indexPositive[i][0];
        for (int j = 0; j < A; ++j)
        {
            if (minp > indexPositive[i][j])
                minp = indexPositive[i][j];
        }
        minPositive[i] = minp;
        cout << minPositive[i]<< endl;
    }
    //максимум среди строк в индексе несогласия
    double maxNegative[N];
    double maxn;
    for (int i = 0; i < A; ++i)
    {
        maxn = indexNegative[i][0];
        for (int j = 0; j < A; ++j)
        {
            if (maxn < indexNegative[i][j])
                maxn = indexNegative[i][j];
        }
        maxNegative[i] = maxn; 
        cout << maxNegative[i] << endl;
    }
    double C, D;
    cout << "Введите пороговые значения индексов согласия и несогласия:" << endl;
    cin >> C >> D;
    cout << endl;
    cout << "Подходящие по индексу согласия альтернативы: ";
    for (int i = 0; i < A; i++)
    {
        if (minPositive[i] > C)
        {
            cout.width(3);
            cout << "A" << i + 1 << endl;
        }
    }
    cout << endl;
    cout << "Подходящие по индексу согласия альтернативы: ";
    for (int i = 0; i < A; i++)
    {
        if (maxNegative[i] < D)
        {
            cout.width(3);
            cout << "A" << i + 1 << endl;
        }
    }
    return 0;
}