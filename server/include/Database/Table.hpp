// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Table.hpp created 28/09/2017

#pragma once

#include <fstream>
#include <exception>
#include <iostream>
#include "ITable.hpp"

namespace Database
{
    class Table : public ITable
    {
      private:
        Rows _rows;
        std::string _tableName;
        std::string _dbName;
        Id   _lastId;
        std::function<void(std::ofstream &, const Rows &)> _saveFunction = [] (std::ofstream &, const Rows &) {
            LOG.error("[TABLE] You need to set a save function for this table !");
        };


      public:
        const std::string &getTableName() const override;
        explicit Table(const std::string &tableName, const std::string &dbName);
        ~Table() override;

        ITable &parse(std::function<void(std::ifstream &, Rows &)> func) override;
        ITable &addField(const Field &field) override;
        ITable &addRow(const std::map<Field, Data> &row) override;
        ITable &clear() override;
        ITable &delRow(Database::Id ID) override;
        const std::vector<Field> getColumnsName() const override;
        Row getRow(std::function<bool(Row)>) override;
        std::vector<Row> getRows(std::function<bool(Row)>) override;
        void print() override;
        ITable &removeField(const Field &field) override;
        ITable &setSaveFunction(std::function<void(std::ofstream &, const Rows &)> func) override;
        ITable &save() override;
        ITable &updateField(const Database::Field &field, const Database::Field &newField) override;
        ITable &updateRow(const Row &row) override;
        ITable &renameTable(const std::string &newTableName) override;
    };
}