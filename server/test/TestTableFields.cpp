// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TestTableFields.cpp created 01/10/2017

#include <gtest/gtest.h>
#include "DatabaseTXT.hpp"
#include "Table.hpp"

TEST(TABLE_GET_COLUMNS__Test, TABLE__Test)
{
    Database::ITable    *table = new Database::Table("User", "./database");
    const Database::Field   fields[] =
        {
            "nickname",
            "password",
            "username",
        };

    for (const auto &field : fields)
        table->addField(field);

    const std::vector<Database::Field> fieldsNames = table->getColumnsName();
    for (int i = 0; i < fieldsNames.size(); i++)
        ASSERT_EQ(fields[i], fieldsNames[i]);
}

TEST(TABLE_RENAME, TABLE_RENAME_Test)
{
    Database::IDatabase *database = new Database::DatabaseTXT();

    database->addTable("User");
    ASSERT_EQ("User", database->getTable("User")->getTableName());

    database->renameTable("User", "Users");
    ASSERT_EQ("Users", database->getTable("Users")->getTableName());
}

TEST(TABLE_ROW, TABLE_ROW_Test)
{
    Database::ITable    *table = new Database::Table("User", "./database");
    const Database::Field   fields[] =
        {
            "nickname",
            "password",
            "username",
        };

    for (const auto &field : fields)
        table->addField(field);

    std::map<Database::Field, Database::Data> map;

    map["username"] = "lopez";
    table->addRow(map);

    auto x = "lopez";

    auto test = table->getRow([x] (Database::Row r) -> bool {
        return r.first["username"] == x;
    });

    ASSERT_EQ(test.first["username"], x);

}