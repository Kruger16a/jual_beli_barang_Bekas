// Membuat backend untuk "Jual dan Beli Barang Bekas" dengan alur bisnis utama
// dan endpoint CRUD untuk setiap entitas utama



#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <limits>

struct User {
    int id;
    std::string name;
    std::string email;
    std::string phone;
};

struct Item {
    int id;
    std::string name;
    std::string description;
    double price;
    bool isAvailable;
};

struct Transaction {
    int id;
    int sellerId;
    int buyerId;
    int itemId;
    std::string status; // "Pending", "Completed", "Cancelled"
};

class Backend {
private:
    std::vector<User> users;
    std::vector<Item> items;
    std::vector<Transaction> transactions;

    int generateId() {
        static int currentId = 1;
        if (currentId == std::numeric_limits<int>::max()) {
            throw std::overflow_error("ID telah mencapai batas maksimum.");
        }
        return currentId++;
    }

public:
    // CRUD untuk User
    int createUser(const std::string& name, const std::string& email, const std::string& phone) {
        User user = { generateId(), name, email, phone };
        users.push_back(user);
        return user.id;
    }

    std::optional<User> getUser(int id) {
        for (const auto& user : users) {
            if (user.id == id) {
                return user;
            }
        }
        return std::nullopt;
    }

    bool updateUser(int id, const std::string& name, const std::string& email, const std::string& phone) {
        for (auto& user : users) {
            if (user.id == id) {
                user.name = name;
                user.email = email;
                user.phone = phone;
                return true;
            }
        }
        return false;
    }

    bool deleteUser(int id) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->id == id) {
                users.erase(it);
                return true;
            }
        }
        return false;
    }

    // CRUD untuk Item
    int createItem(const std::string& name, const std::string& description, double price) {
        Item item = { generateId(), name, description, price, true };
        items.push_back(item);
        return item.id;
    }

    std::optional<Item> getItem(int id) {
        for (const auto& item : items) {
            if (item.id == id) {
                return item;
            }
        }
        return std::nullopt;
    }

    bool updateItem(int id, const std::string& name, const std::string& description, double price, bool isAvailable) {
        for (auto& item : items) {
            if (item.id == id) {
                item.name = name;
                item.description = description;
                item.price = price;
                item.isAvailable = isAvailable;
                return true;
            }
        }
        return false;
    }

    bool deleteItem(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->id == id) {
                items.erase(it);
                return true;
            }
        }
        return false;
    }

    // CRUD untuk Transaction
    int createTransaction(int sellerId, int buyerId, int itemId, const std::string& status) {
        Transaction transaction = { generateId(), sellerId, buyerId, itemId, status };
        transactions.push_back(transaction);
        return transaction.id;
    }

    std::optional<Transaction> getTransaction(int id) {
        for (const auto& transaction : transactions) {
            if (transaction.id == id) {
                return transaction;
            }
        }
        return std::nullopt;
    }

    bool updateTransaction(int id, const std::string& status) {
        for (auto& transaction : transactions) {
            if (transaction.id == id) {
                transaction.status = status;
                return true;
            }
        }
        return false;
    }

    bool deleteTransaction(int id) {
        for (auto it = transactions.begin(); it != transactions.end(); ++it) {
            if (it->id == id) {
                transactions.erase(it);
                return true;
            }
        }
        return false;
    }
};

void displayMenu() {
    std::cout << "\n==== Menu ====" << std::endl;
    std::cout << "1. Tambah User" << std::endl;
    std::cout << "2. Lihat User" << std::endl;
    std::cout << "3. Update User" << std::endl;
    std::cout << "4. Hapus User" << std::endl;
    std::cout << "5. Tambah Item" << std::endl;
    std::cout << "6. Lihat Item" << std::endl;
    std::cout << "7. Update Item" << std::endl;
    std::cout << "8. Hapus Item" << std::endl;
    std::cout << "9. Tambah Transaksi" << std::endl;
    std::cout << "10. Lihat Transaksi" << std::endl;
    std::cout << "11. Update Transaksi" << std::endl;
    std::cout << "12. Hapus Transaksi" << std::endl;
    std::cout << "0. Keluar" << std::endl;
    std::cout << "Pilih opsi: ";
}

int main() {
    Backend backend;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input tidak valid, coba lagi." << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string name, email, phone;
                std::cout << "Masukkan nama: ";
                std::getline(std::cin, name);
                std::cout << "Masukkan email: ";
                std::getline(std::cin, email);
                std::cout << "Masukkan nomor telepon: ";
                std::getline(std::cin, phone);
                int id = backend.createUser(name, email, phone);
                std::cout << "User berhasil ditambahkan dengan ID: " << id << std::endl;
                break;
            }
            case 2: {
                int id;
                std::cout << "Masukkan ID User: ";
                std::cin >> id;
                auto user = backend.getUser(id);
                if (user) {
                    std::cout << "Nama: " << user->name << ", Email: " << user->email << ", Telepon: " << user->phone << std::endl;
                } else {
                    std::cout << "User tidak ditemukan." << std::endl;
                }
                break;
            }
            case 3: {
                int id;
                std::string name, email, phone;
                std::cout << "Masukkan ID User: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Masukkan nama baru: ";
                std::getline(std::cin, name);
                std::cout << "Masukkan email baru: ";
                std::getline(std::cin, email);
                std::cout << "Masukkan nomor telepon baru: ";
                std::getline(std::cin, phone);
                if (backend.updateUser(id, name, email, phone)) {
                    std::cout << "User berhasil diperbarui." << std::endl;
                } else {
                    std::cout << "User tidak ditemukan." << std::endl;
                }
                break;
            }
            case 4: {
                int id;
                std::cout << "Masukkan ID User: ";
                std::cin >> id;
                if (backend.deleteUser(id)) {
                    std::cout << "User berhasil dihapus." << std::endl;
                } else {
                    std::cout << "User tidak ditemukan." << std::endl;
                }
                break;
            }
            case 5: {
                std::string name, description;
                double price;
                std::cout << "Masukkan nama item: ";
                std::getline(std::cin, name);
                std::cout << "Masukkan deskripsi item: ";
                std::getline(std::cin, description);
                std::cout << "Masukkan harga item: ";
                std::cin >> price;
                int id = backend.createItem(name, description, price);
                std::cout << "Item berhasil ditambahkan dengan ID: " << id << std::endl;
                break;
            }
            case 6: {
                int id;
                std::cout << "Masukkan ID Item: ";
                std::cin >> id;
                auto item = backend.getItem(id);
                if (item) {
                    std::cout << "Nama: " << item->name << ", Deskripsi: " << item->description << ", Harga: " << item->price << ", Tersedia: " << (item->isAvailable ? "Ya" : "Tidak") << std::endl;
                } else {
                    std::cout << "Item tidak ditemukan." << std::endl;
                }
                break;
            }
            case 7: {
                int id;
                std::string name, description;
                double price;
                bool isAvailable;
                std::cout << "Masukkan ID Item: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Masukkan nama baru: ";
                std::getline(std::cin, name);
                std::cout << "Masukkan deskripsi baru: ";
                std::getline(std::cin, description);
                std::cout << "Masukkan harga baru: ";
                std::cin >> price;
                std::cout << "Tersedia (1 untuk Ya, 0 untuk Tidak): ";
                std::cin >> isAvailable;
                if (backend.updateItem(id, name, description, price, isAvailable)) {
                    std::cout << "Item berhasil diperbarui." << std::endl;
                } else {
                    std::cout << "Item tidak ditemukan." << std::endl;
                }
                break;
            }
            case 8: {
                int id;
                std::cout << "Masukkan ID Item: ";
                std::cin >> id;
                if (backend.deleteItem(id)) {
                    std::cout << "Item berhasil dihapus." << std::endl;
                } else {
                    std::cout << "Item tidak ditemukan." << std::endl;
                }
                break;
            }
            case 9: {
                int sellerId, buyerId, itemId;
                std::string status;
                std::cout << "Masukkan ID Penjual: ";
                std::cin >> sellerId;
                std::cout << "Masukkan ID Pembeli: ";
                std::cin >> buyerId;
                std::cout << "Masukkan ID Item: ";
                std::cin >> itemId;
                std::cin.ignore();
                std::cout << "Masukkan status (Pending/Completed/Cancelled): ";
                std::getline(std::cin, status);
                int id = backend.createTransaction(sellerId, buyerId, itemId, status);
                std::cout << "Transaksi berhasil ditambahkan dengan ID: " << id << std::endl;
                break;
            }
            case 10: {
                int id;
                std::cout << "Masukkan ID Transaksi: ";
                std::cin >> id;
                auto transaction = backend.getTransaction(id);
                if (transaction) {
                    std::cout << "ID Penjual: " << transaction->sellerId << ", ID Pembeli: " << transaction->buyerId
                              << ", ID Item: " << transaction->itemId << ", Status: " << transaction->status << std::endl;
                } else {
                    std::cout << "Transaksi tidak ditemukan." << std::endl;
                }
                break;
            }
            case 11: {
                int id;
                std::string status;
                std::cout << "Masukkan ID Transaksi: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Masukkan status baru (Pending/Completed/Cancelled): ";
                std::getline(std::cin, status);
                if (backend.updateTransaction(id, status)) {
                    std::cout << "Transaksi berhasil diperbarui." << std::endl;
                } else {
                    std::cout << "Transaksi tidak ditemukan." << std::endl;
                }
                break;
            }
            case 12: {
                int id;
                std::cout << "Masukkan ID Transaksi: ";
                std::cin >> id;
                if (backend.deleteTransaction(id)) {
                    std::cout << "Transaksi berhasil dihapus." << std::endl;
                } else {
                    std::cout << "Transaksi tidak ditemukan." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Keluar dari program." << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

