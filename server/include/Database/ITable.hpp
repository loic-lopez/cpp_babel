// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// ITable.hpp created 28/09/2017

#pragma once

#include <vector>
#include <map>
#include <functional>
#include <boost/any.hpp>

namespace Database
{
    /// \brief name of the field in Database
    using Field = std::string;

    /// \brief Id of a user
    using Id = unsigned;

    /// \brief Data: used to store data from users
    using Data = std::string;

    /// \brief needed to return a single row
    using Row = std::pair<std::map<Field, Data>, Id>;

    /// \brief used to create rows in database
    using Rows = std::map<Field, std::map<Id, Data>>;

    class ITable
    {
      public:
        virtual ~ITable() { };

        virtual ITable &addField(const Field &) = 0;
        virtual const std::string &getTableName() const = 0;
        virtual ITable &parse(std::function<void (std::ifstream &, Rows &)> func) = 0;
        virtual ITable &addRow(const std::map<Field, Data> &row) = 0;
        virtual ITable &clear() = 0;
        virtual ITable &delRow(Database::Id ID) = 0;
        virtual const std::vector<Field> getColumnsName() const = 0;
        virtual std::vector<Row> getRows(std::function<bool(Row)>) = 0;
        virtual Row getRow(std::function<bool(Row)>) = 0;
        virtual void print() = 0;
        virtual ITable &removeField(const Field &) = 0;
        virtual ITable &setSaveFunction(std::function<void(std::ofstream &, const Rows &)> func) = 0;
        virtual ITable &save() = 0;
        virtual ITable &updateField(const Database::Field &field, const Database::Field &newField) = 0;
        virtual ITable &updateRow(const Row &row) = 0;
        virtual ITable &renameTable(const std::string &newTableName) = 0;

        class TableAlreadyExist : std::exception
        {
          private:
            std::string msg;

          public:
            explicit TableAlreadyExist(const std::string &tableName) : msg(tableName + ": already exists.")
            {
            }

            TableAlreadyExist(const TableAlreadyExist &tableAlreadyExist) noexcept
            {
                this->msg = tableAlreadyExist.msg;
            }


            TableAlreadyExist &operator=(const TableAlreadyExist &tableAlreadyExist) noexcept
            {
                if (this != &tableAlreadyExist)
                    this->msg = tableAlreadyExist.msg;
                return *this;
            }

            virtual ~TableAlreadyExist() {}

            virtual const char *what() const throw()
            {
                return msg.c_str();
            }
        };

    };
}
