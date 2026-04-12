#ifndef PTECH_TAXPAYER_HPP
#define PTECH_TAXPAYER_HPP
#include <sstream>
#include <string>

/**
 * Class representing a taxpayer with their details such as name, last name, inn and tax amount
 */
class Taxpayer {
public:
    /**
     * Full name of the taxpayer
     */
    std::string fio;
    /**
     * Taxpayer Identification Number (INN)
     */
    std::string inn;
    /**
     * Address of the taxpayer
     */
    std::string address;
    /**
     * Amount of tax paid this year by the taxpayer
     */
    double tax_amount;

    /**
     * @param f Full name of the taxpayer
     * @param i Taxpayer Identification Number (INN)
     * @param a Address of the taxpayer
     * @param t Amount of tax paid this year by the taxpayer
     */
    Taxpayer(std::string f, std::string i, std::string a, const double t)
        : fio(std::move(f)), inn(std::move(i)), address(std::move(a)), tax_amount(t) {
    }

    /**
     *
     * @param other Another taxpayer to compare with
     * @return true if this taxpayer is less than the other taxpayer, false otherwise.
     *  Comparison is done first by full name (fio) and then by inn if full names are equal.
     */
    bool operator<(const Taxpayer &other) const {
        return fio != other.fio ? fio < other.fio : inn < other.inn;
    }

    /**
     * @param other Another taxpayer to compare with
     * @return true if this taxpayer is equal to the other taxpayer, false otherwise.
     *  Two taxpayers are considered equal if they have the same full name (fio) and inn.
     */
    bool operator>(const Taxpayer &other) const {
        return other < *this;
    }

    /**
     * @param other Another taxpayer to compare with
     * @return true if this taxpayer is equal to the other taxpayer, false otherwise.
     *  Two taxpayers are considered equal if they have the same full name (fio) and inn.
     */
    bool operator<=(const Taxpayer &other) const {
        return !(*this > other);
    }

    /**
     * @param other Another taxpayer to compare with
     * @return true if this taxpayer is equal to the other taxpayer, false otherwise.
     *  Two taxpayers are considered equal if they have the same full name (fio) and inn.
     */
    bool operator>=(const Taxpayer &other) const {
        return !(*this < other);
    }
};

/**
 * Read data from CSV
 *
 * @param filename File name to read the data from
 * @return Vector of Taxpayer objects read from the file
 */
static std::vector<Taxpayer> readData(const std::string &filename) {
    std::vector<Taxpayer> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string f, i, a, t_str;
        std::getline(ss, f, ',');
        std::getline(ss, i, ',');
        std::getline(ss, a, ',');
        std::getline(ss, t_str, ',');
        double t = std::stod(t_str);
        data.emplace_back(f, i, a, t);
    }
    return data;
}

/**
 * Write vector data to CSV
 *
 * @param filename File name to save the data
 * @param data Vector of Taxpayer objects to be saved
 */
static void writeData(const std::string &filename, const std::vector<Taxpayer> &data) {
    std::ofstream file(filename);
    file << "\xEF\xBB\xBF"; // bom utf-8
    for (const auto &p: data) {
        file << p.fio << "," << p.inn << "," << p.address << "," << p.tax_amount << "\n";
    }
}

#endif //PTECH_TAXPAYER_HPP
