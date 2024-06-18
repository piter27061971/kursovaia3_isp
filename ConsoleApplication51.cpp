// ConsoleApplication51.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
 
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
//using namespace std;

void udal_toshka_s_zapiatoi(std::string & stroka) // удаление комментариев в строке
{
    int kol_elem = stroka.size();
    int num_toska_zap = 0;
    bool kommentari_v_stroke=false;
    for (int i = 0; i < kol_elem; i++)
    {
        if (stroka[i] == ';')
        {
            kommentari_v_stroke = true;
            num_toska_zap = i;
            break;
        }
    }
    if (kommentari_v_stroke)
    {
        stroka = stroka.substr(0, num_toska_zap);
    }
    

}

void udal_prob(std::string& stroka)  // Удаление пробелов и табуляций в строке
{   int n1 = 0;
    int n2 = stroka.size();
    if ((n2) != 0) 
    { 
    
    while ((n2>0)&&((stroka[n2-1] == ' ') || (stroka[n2-1] == '\t')))
    {
        --n2;
    }
    if ((n2) != 0)
    {
   
    while ((stroka[n1] == ' ') || (stroka[n1] == '\t'))
    {
        ++n1;
    } 
    }
     stroka= stroka.substr(n1, (n2 - n1));
    }
}

class ini_parser
{
public:
    ini_parser(std::string fail) : put_fail{ fail }
    {
        
        
    }
    template <typename T> T get_value(std::string value_section)
    {
        
        std::string str_iskl;
        std::string obr_str;
        std::string str_secsii;
        std::string variant="var0";
        std::string vozvrat1;
        T vr, vozvr;
        int kol_naiden_param = 0;
        int num_secii;
        int num_tek_str=0;
        int num_obr_str=0;
        int num_neobr_str=0;
        std::ifstream fin_exist(put_fail);
        ukaz.open(put_fail);
        if (!ukaz.is_open())
        {
            str_iskl="Не получилось открыть файл "+ put_fail+". Возможно введено неправильное имя!";
            throw str_iskl;
        } //  if (ukaz.is_open())
        else {
        try
        {
            num_secii = stoi(value_section);
        }
        catch (...)
        {
            ukaz.close();
            str_iskl = "Номер секции не является целым числом. Вы ввели="+ value_section;
            throw str_iskl;
        }
        str_secsii = "[Section" + value_section + "]";
        udal_prob(str_secsii);
        std::string name = typeid(vr).name();
        //std::cout << name << std::endl;
        if ((name == "int")||(name == "double")||(name == "float")) variant="var1=";
        if (variant == "var0") 
        { 
            ukaz.close();
            str_iskl=("Нет обработчика соответствующего типа "+name);
            throw str_iskl;
        }
       
        while (!ukaz.eof())
        {
            std::getline(ukaz, obr_str);
            ++num_tek_str;            
            udal_toshka_s_zapiatoi(obr_str);
            udal_prob(obr_str);
            //std::cout << obr_str << std::endl;
            if (obr_str == str_secsii)
                //if (obr_str == obr_str)

            {
                while (!ukaz.eof())
                {
                    std::getline(ukaz, obr_str);
                    ++num_tek_str;
                    udal_toshka_s_zapiatoi(obr_str);
                    udal_prob(obr_str);
                    if ((obr_str.substr(0, 8) == "[Section") && (obr_str.substr(0, str_secsii.size()) != str_secsii))
                    {
                        break;
                    }
                    if (obr_str.substr(0, variant.size()) == variant)
                    {
                        obr_str = obr_str.substr(variant.size(), (obr_str.size() - variant.size()));
                        udal_prob(obr_str);
                        kol_naiden_param++;
                            if (name == "int")
                            {
                                try
                                {
                                    vr = stoi(obr_str);
                                    vozvr = vr;
                                    num_obr_str = num_tek_str;
                                    vozvrat1=obr_str;
                                    continue;
                                }
                                catch (...)
                                {
                                    num_neobr_str = num_tek_str;
                                    continue;
                                }                                
                            }

                            if (name == "double")
                            {
                                try
                                {
                                    vr = stod(obr_str);
                                    vozvr = vr;
                                    num_obr_str = num_tek_str;
                                    vozvrat1 = obr_str;
                                    continue;
                                }
                                catch (...)
                                {
                                    num_neobr_str = num_tek_str;
                                    continue;
                                }
                            }
                                if (name == "float")
                                {
                                    try
                                    {
                                        vr = stof(obr_str);
                                        vozvr = vr;
                                        num_obr_str = num_tek_str;
                                        vozvrat1 = obr_str;
                                        continue;
                                    }
                                    catch (...)
                                    {
                                        num_neobr_str = num_tek_str;
                                        continue;
                                    }
                                } 
                    }

                }
            }
        }
        ukaz.close();
        //std::cout << "текущая строка " << num_tek_str << std::endl;
        if (num_obr_str > num_neobr_str)
        {
            return vozvr;
        }
        else 
        {
            if (num_obr_str == 0)
            {
                if (num_neobr_str!=0)
                { 
                    str_iskl=("Искомый параметр найден в строке " + std::to_string(num_neobr_str) + " Но его не удается правильно обработать." + 
                        " Всего количество строк с искомым параметром равно "+ std::to_string(kol_naiden_param));
                //std::cout << ("Искомый параметр найден в строке " + std::to_string(num_neobr_str) + " Но его не удается правильно обработать.") << std::endl;
                throw str_iskl;
                }//if (num_neobr_str!=0)
                else
                {
                    str_iskl = "Искомый параметр не найден";
                    throw str_iskl;
                }// else if (num_neobr_str!=0)
            } //if (num_obr_str == 0)
            else
            {
                str_iskl = ("Искомый параметр найден в строке " + std::to_string(num_neobr_str) +
                    " Но его не удается правильно обравботать. Но при этом раньше в строке " + std::to_string(num_obr_str)
                    + " был искомый параметр и его значение равно " + vozvrat1+
                    "Всего найденных параметров равно " + std::to_string(kol_naiden_param));
                throw str_iskl;
            }// else if (num_obr_str == 0)
        }
        }// else  if (!ukaz.is_open())
    }
template <>
std::string get_value (std::string value_section)
{
    
    std::string str_iskl;
    std::string obr_str;
    std::string str_secsii;
    std::string variant = "var2=";
    std::string vozvrat1;
    std::string vozvr;
    int kol_naiden_param = 0;
    int num_secii;
    int num_tek_str = 0;
    int num_obr_str = 0;
    int num_neobr_str = 0;
    std::ifstream fin_exist(put_fail);
    ukaz.open(put_fail);
    if (!ukaz.is_open())
    {
        //std::cout << "Не получилось открыть файл!" << std::endl; 
        str_iskl = "Не получилось открыть файл " + put_fail + ". Возможно введено неправильное имя!";
        throw str_iskl;
    } //  if (ukaz.is_open())
    else {
        try
        {
            num_secii = stoi(value_section);
        }
        catch (...)
        {
            ukaz.close();
            str_iskl = "Номер секции не является целым числом. Вы ввели=" + value_section;
            throw str_iskl;
        }
        str_secsii = "[Section" + value_section + "]";
        

        while (!ukaz.eof())
        {
            std::getline(ukaz, obr_str);
            ++num_tek_str;
            udal_toshka_s_zapiatoi(obr_str);
            udal_prob(obr_str);
            if (obr_str == str_secsii)
            {
                while (!ukaz.eof())
                {
                    std::getline(ukaz, obr_str);
                    ++num_tek_str;
                    udal_toshka_s_zapiatoi(obr_str);
                    udal_prob(obr_str);
                    if ((obr_str.substr(0, 8) == "[Section") && (obr_str.substr(0, str_secsii.size()) != str_secsii))
                    {
                        break;
                    }
                    if (obr_str.substr(0, variant.size()) == variant)
                    {
                        obr_str = obr_str.substr(variant.size(), (obr_str.size() - variant.size()));
                        udal_prob(obr_str);
                        vozvr = obr_str;
                        num_obr_str = num_tek_str;
                        vozvrat1 = obr_str;
                        continue;
                        }
                    }

                }
            }

        }
          ukaz.close();
        return vozvr ;
}
private:
    std::string put_fail;
    std::ifstream ukaz;
};


int main()
{
    setlocale(LC_ALL, "");

    ini_parser B("123.ini");

    try
    {
      std::cout<< B.get_value<double>("1")<<std::endl;
     
    }
    catch (std::string & error_message)
    {
        std::cout << error_message << std::endl;
    }

    ini_parser B2("123.ini");
    try
    {
        std::cout << B2.get_value<std::string>("1") << std::endl;

    }
    catch (std::string& error_message)
    {
        std::cout << error_message << std::endl;
    }
   
    ini_parser B3("1.ini");
    try
    {
        std::cout << B3.get_value<double>("2") << std::endl;

    }
    catch (std::string& error_message)
    {
        std::cout << error_message << std::endl;
    }
    ini_parser B4("2.ini");
    try
    {
        std::cout << B4.get_value<double>("2") << std::endl;

    }
    catch (std::string& error_message)
    {
        std::cout << error_message << std::endl;
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
