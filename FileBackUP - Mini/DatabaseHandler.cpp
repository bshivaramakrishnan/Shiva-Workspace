// DatabaseHandler.cpp
#include "DatabaseHandler.h"
#include <iostream>
#include <sstream>

sqlite3* DatabaseUtil::sqliteDB = nullptr;
bool DatabaseUtil::isConnEstablished = false;
bool DatabaseUtil::isPostgresDBConnEnabled = false;
bool DatabaseUtil::isSqliteDBConnEnabled = false;

const std::string DatabaseUtil::SERVER_DB_FILE_NAME = "serverDB.db";
const std::string DatabaseUtil::CLIENT_DB_FILE_NAME = "clientDB.db";

void DatabaseUtil::Initialize() {
    sqliteDB = nullptr;
    isConnEstablished = false;
    isPostgresDBConnEnabled = false;
    isSqliteDBConnEnabled = false;
}

bool DatabaseUtil::AuthenticateUser(const std::string& username, const std::string& password) {
    std::string sql = "SELECT id FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(sqliteDB) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    bool isAuthenticated = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        isAuthenticated = true;
    }

    sqlite3_finalize(stmt);
    return isAuthenticated;
}

int DatabaseUtil::GetUserId(const std::string& username) {
    std::string sql = "SELECT id FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    int userId = -1;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return userId;
}

void DatabaseUtil::EstablishDBConnection(const std::string& a_dbFileName) {
    std::cout << "Inside EstablishDBConnection \n";
    if (sqlite3_open(a_dbFileName.c_str(), &sqliteDB) == SQLITE_OK) {
        std::cout << "SQLite connected successfully!" << std::endl;
        isConnEstablished = true;

        sqlite3_exec(sqliteDB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
        InitializeDatabase();
    }
    else {
        std::cout << "Failed to connect to SQLite." << std::endl;
        isConnEstablished = false;
    }
}

void DatabaseUtil::UpdateTable(const std::string& username, const std::string& password) {
    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(sqliteDB) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(sqliteDB) << std::endl;
    }
    else {
        std::cout << "User '" << username << "' registered successfully.\n";
    }

    sqlite3_finalize(stmt);
}

void DatabaseUtil::CloseDBConnection() {
    if (sqliteDB) {
        sqlite3_close(sqliteDB);
        sqliteDB = nullptr;
        std::cout << "Database connection closed successfully." << std::endl;
    }
    else {
        std::cout << "Database connection already closed or not initialized." << std::endl;
    }
}

std::string DatabaseUtil::GetBackupPath(int userId, const std::string& filename) {
    std::string path;
    std::string sql = "SELECT filepath FROM backups WHERE user_id = ? AND filename = ? LIMIT 1;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return path;
    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, filename.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        path = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    LogOperation(userId, "Requested restore: " + filename);
    return path;
}

void DatabaseUtil::LogOperation(int userId, const std::string& operation) {
    std::string sql = "INSERT INTO logs (user_id, operation) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return;

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, operation.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

bool DatabaseUtil::DeleteBackup(int userId, const std::string& filename) {
    std::string sql = "DELETE FROM backups WHERE user_id = ? AND filename = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, filename.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    LogOperation(userId, "Deleted backup: " + filename);
    return success;
}

std::vector<std::string> DatabaseUtil::ListBackups(int userId) {
    std::vector<std::string> backups;
    std::string sql = "SELECT filename FROM backups WHERE user_id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return backups;
    sqlite3_bind_int(stmt, 1, userId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        backups.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    }

    sqlite3_finalize(stmt);
    LogOperation(userId, "Listed backups");
    return backups;
}

bool DatabaseUtil::SaveBackupMetadata(int userId, const std::string& filename, const std::string& filepath) {
    std::string sql = "INSERT INTO backups (user_id, filename, filepath) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(sqliteDB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) return false;

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, filename.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, filepath.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    LogOperation(userId, "Backup configured: " + filename);
    return success;
}

std::map<int, std::map<std::string, std::string>> DatabaseUtil::Execquery(const std::string& query) {
    sqlite3_stmt* stmt = nullptr;
    std::map<int, std::map<std::string, std::string>> tableData;

    int rc = sqlite3_prepare_v2(sqliteDB, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(sqliteDB) << std::endl;
        return tableData;
    }

    int rowIndex = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int colCount = sqlite3_column_count(stmt);
        std::map<std::string, std::string> rowMap;

        for (int i = 0; i < colCount; ++i) {
            const char* colName = sqlite3_column_name(stmt, i);
            const unsigned char* text = sqlite3_column_text(stmt, i);

            rowMap[colName] = text ? reinterpret_cast<const char*>(text) : "";
        }

        tableData.emplace(rowIndex++, std::move(rowMap));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error stepping through rows: " << sqlite3_errmsg(sqliteDB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return tableData;
}

void DatabaseUtil::InitializeDatabase() {
    const char* createTablesSQL =
        "BEGIN TRANSACTION;"

        "CREATE TABLE IF NOT EXISTS users ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   username TEXT UNIQUE NOT NULL,"
        "   password TEXT NOT NULL,"
        "   email TEXT,"
        "   created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "   last_login TIMESTAMP,"
        "   is_active BOOLEAN DEFAULT 1"
        ");"

        "CREATE TABLE IF NOT EXISTS backups ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   user_id INTEGER NOT NULL,"
        "   filename TEXT NOT NULL,"
        "   filepath TEXT NOT NULL,"
        "   filesize INTEGER,"
        "   backup_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "   last_modified TIMESTAMP,"
        "   is_encrypted BOOLEAN DEFAULT 0,"
        "   compression_type TEXT,"
        "   version INTEGER DEFAULT 1,"
        "   FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,"
        "   UNIQUE(user_id, filename)"
        ");"

        "CREATE TABLE IF NOT EXISTS logs ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   user_id INTEGER NOT NULL,"
        "   operation TEXT NOT NULL,"
        "   timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "   ip_address TEXT,"
        "   status TEXT,"
        "   details TEXT,"
        "   FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE"
        ");"

        "CREATE INDEX IF NOT EXISTS idx_backups_user ON backups(user_id);"
        "CREATE INDEX IF NOT EXISTS idx_logs_user ON logs(user_id);"
        "CREATE INDEX IF NOT EXISTS idx_logs_timestamp ON logs(timestamp);"

        "INSERT OR IGNORE INTO users (username, password, email) VALUES ('admin', 'admin123', 'admin@example.com');"
        "INSERT OR IGNORE INTO users (username, password, email) VALUES ('user1', 'user123', 'user1@example.com');"
        "INSERT OR IGNORE INTO users (username, password, email) VALUES ('user2', 'pass456', 'user2@example.com');"
        "INSERT OR IGNORE INTO users (username, password, email) VALUES ('mani', 'mani', 'user4@example.com');"
        "COMMIT;";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(sqliteDB, createTablesSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Database initialization failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Database tables and hardcoded users initialized successfully." << std::endl;
    }
}