/*

    Project: Basic MARCH86 Project
    Architecture : MARCH86/v2.0

*/

#include <iostream>
#include <string>
#include <functional>
#include <map>

class Processor
{
    private:
        std::string mem[512] = {};
        std::map<int, std::function<int()>> endPoints = {{}};
        /*
        CPU Options
        Can be modified to create your own CPU's universe, so, prefer to not change anything if you don't understand this anything there.
        */
        int OSLocation = 72;
        std::string CPUName = "MARCH86A98DB9";

        /*
        Memory Functions

        Going to be used by Processor to verify arguments to work with the Memory and execute tasks on it.

        */
        void ValidateMessage(std::string text)
        {
            if (text.length() > 50){std::cout << "CPU Stopped : ERROR 700F" << std::endl; exit(700);}
        }
        void ValidateAddress(int address)
        {
            if (address > sizeof mem){std::cout << "CPU Stopped : ERROR A70" << std::endl; exit(70);}
        }
    public:
        int test(int address1, int address2, char type)
        {
            ValidateAddress(address1);
            ValidateAddress(address2);

            std::map<char, int> types = {
                {
                    '=', 0
                },
                {
                    '>', 1
                },
                {
                    '<', 2
                }
            };
            switch(types[type])
            {
                case 0:
                    if (mem[address1] == mem[address2])
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                case 1:
                    if (mem[address1] > mem[address2])
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                case 2:
                    if (mem[address1] < mem[address2])
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
            }
        }
        int wrt(int address, std::string text)
        {
            ValidateAddress(address);
            ValidateMessage(text);
            if (mem[address] == "FF2ZS6ZT29YXOFYDMWJVLO6YWS53IXEJGOQ0FGNUQALYCPME06")
            {
                std::cout << "CPU WARN: Can't write! You are about to damage the ROM! Is a protected area." << std::endl;
                return 90;
            }
            mem[address] = text;
            return 0;
        }
        int nep(int address, std::function<int()> EndPoint)
        {
            ValidateAddress(address);
            if (endPoints.count(address) > 0){std::cout << "CPU Warn : Already in use. OPERATION : MOV [YourEndPoint], " << address << std::endl; return 90;}

            endPoints.insert({{address, EndPoint}});
            return 0;
        }
        void jmp(int address)
        {
            ValidateAddress(address);

            endPoints[address]();
        }
        void loop(int address, int dountil)
        {
            while(mem[dountil] != "0x8000")
            {
                endPoints[address]();
            }
        }
        void mov(int address1, int address2)
        {
            ValidateAddress(address1);
            ValidateAddress(address2);

            wrt(address1, mem[address2]);
        }
};
