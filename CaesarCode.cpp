#include <iostream>
#include <string>
#include <sstream> //stringstream
//#include <cstdlib> //exit()
#include <fstream>

void setnKey(int &nKey)
{
    while(1)
    {
        std::string strKey;
        std::cout << "Enter key:\n";
        std::cin >> strKey;

        bool bValid = true;

        if (strKey[0] == '-' && isgraph(strKey[1])){}
        else if (!isdigit(strKey[0]))
            continue;
        for (unsigned int i = 1; i < strKey.length(); i++)
        {
            if (!isdigit(strKey[i]))
            {
                bValid = false;
                break;
            }
        }

        if (!bValid)
            continue;
        
        std::stringstream strStream;
        strStream << strKey;
        strStream >> nKey;

        break;
    }

}

void caesarCipherString(std::string &strMassege, int &nKey)
{
    for (char &symb : strMassege)
    {
        if (isalpha(symb) && symb >= 'a' && symb <= 'z')
        {
            int tmpKey = nKey;
            tmpKey %= 26;
            tmpKey += 26;
            symb = char(int(symb + tmpKey - 'a') % 26 + 'a');
        }
        else if (isalpha(symb) && symb >= 'A' && symb <= 'Z')
        {
            int tmpKey = nKey;
            tmpKey %= 26;
            tmpKey += 26;
            symb = char(int(symb + tmpKey - 'A') % 26 + 'A');
        }
        else if (isdigit(symb))
        {
            int tmpKey = nKey;
            tmpKey %= 10;
            tmpKey += 10;
            symb = char(int(symb + tmpKey - '0') % 10 + '0');
        }
        else if (isprint(symb))
        {
            int tmpKey = nKey;
            tmpKey %= 32;
            tmpKey += 32;
            int tmp = int(symb + tmpKey - ' ') % 32;
            if (tmp < 16)
            {
                symb = char(tmp + ' ');
            }
            else if (tmp < 22)
            {
                symb = char(tmp + ' ' + 11); // 11 = 1 + (1 + '9' - '0')
            }
            else if (tmp < 28)
            {
                symb = char(tmp + ' ' + 37); // 37 = 1 + (1 + '9' - '0') + (1 + 'Z' - 'A')
            }
            else if (tmp < 32) 
            {
                symb = char(tmp + ' ' + 63); //63 = 1 + (1 + '9' - '0') + (1 + 'Z' - 'A') + (1 + 'z' - 'a')
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cout << "Enter message:\n";
        std::string strMassege;
        std::getline(std::cin, strMassege);

        int nKey;
        setnKey(nKey);

        caesarCipherString(strMassege, nKey);

        std::cout << strMassege << std::endl;
    }
    else
    {
        for(int count = 1; count < argc; count++)
        {
            std::ifstream readFile(argv[count]);

            std::string outFileName = "cipheredText_";
            outFileName += count + '0';
            outFileName.append(".txt");
            std::cout << outFileName << "\n";
            std::ofstream writeFile(outFileName);

            if(!readFile)
            {
                std::cerr << argv[count] << " could not be opened!" << std::endl;
                continue;
            }

            int nKey;
            setnKey(nKey);

            while (readFile)
            {
                std::string strMassege;
                getline(readFile, strMassege);
                            
                caesarCipherString(strMassege, nKey);

                writeFile << strMassege << std::endl;
            }
        }
    }
    return 0;
}