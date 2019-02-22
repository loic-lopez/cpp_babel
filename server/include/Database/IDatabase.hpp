// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// IDatabase.hpp created 28/09/2017

#pragma once

#include <string>
#include "ITable.hpp"

namespace Database
{
    class IDatabase
    {
      public:
        virtual ~IDatabase()
        {};

        virtual IDatabase &addTable(const std::string &tableName) = 0;
//        virtual IDatabase &addTable(const std::string &tableName,
//                                    std::vector<Field> fields,
//                                    std::function<void(unsigned int, char *, Database::Rows &rows)> func) = 0;
        virtual IDatabase &addFieldToTable(const Field &, const std::string &) = 0;

        virtual ITable *getTable(const std::string &) = 0;
        virtual IDatabase &loadDatabase() = 0;
        virtual IDatabase &print() = 0;
        virtual IDatabase &deleteTable(const std::string &) = 0;
        virtual IDatabase &renameTable(const std::string &, const std::string &) = 0;
        virtual IDatabase &saveTables() = 0;
        virtual IDatabase &setSavefunction(std::function<void(const Rows &rows)>) = 0;

    };
}
