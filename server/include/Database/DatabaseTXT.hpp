// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// DatabaseTXT.hpp created 28/09/2017

#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "IDatabase.hpp"
#include "Logger.hpp"

namespace Database
{
    class DatabaseTXT : public IDatabase
    {
      private:
        std::map<std::string, boost::shared_ptr<ITable *>>   _tables;
        std::string _databaseName;
        bool    _databaseAlreadyExists;
        std::function<void(const Rows &)> _saveFunc;

      public:
        DatabaseTXT(const std::string &databaseName = "./database");
        ~DatabaseTXT() override;

        IDatabase   &addTable(const std::string &tableName) override;
        IDatabase   &addFieldToTable(const Field &, const std::string &) override;
        ITable      *getTable(const std::string &tableName) override;
        IDatabase   &loadDatabase() override;
        IDatabase   &print() override;
        IDatabase   &deleteTable(const std::string &string) override;
        IDatabase   &renameTable(const std::string &string, const std::string &string1) override;
        IDatabase   &saveTables() override;
        IDatabase &setSavefunction(std::function<void(const Rows &)> function) override;
    };
}
