#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <fstream>

class StatisticsCollector {
private:
    std::map<std::string, std::vector<double>> data;

    std::map<std::string, double> thresholds;

public:
    void addData(const std::string& sensorID, double value) {
        data[sensorID].push_back(value);

        if (thresholds.count(sensorID) && value > thresholds[sensorID]) {
            std::cout << "[NOTIFICATION] Аномалия на " << sensorID
                << ": значение " << value << " выше порога "
                << thresholds[sensorID] << "!" << std::endl;
        }
    }

    void setThreshold(const std::string& sensorID, double limit) {
        thresholds[sensorID] = limit;
    }

    double getAverage(const std::string& sensorID) const {
        auto it = data.find(sensorID);
        if (it == data.end() || it->second.empty()) return 0.0;

        double sum = std::accumulate(it->second.begin(), it->second.end(), 0.0);
        return sum / it->second.size();
    }

    double getMax(const std::string& sensorID) const {
        auto it = data.find(sensorID);
        if (it == data.end() || it->second.empty()) return 0.0;

        return *std::max_element(it->second.begin(), it->second.end());
    }

    void saveToCSV(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& item : data) {
            file << item.first;
            for (double val : item.second) {
                file << "," << val;
            }
            file << "\n";
        }
    }
};


struct Time {
    time_t timestamp;
};

class Sensor {
protected:
    std::string sensorID;
    double value = 0.0;
    double calibrationOffset = 0.0;
    Time lastUpdate;

public:
    Sensor(const std::string& id) : sensorID(id) {
        lastUpdate.timestamp = std::time(nullptr);
    }

    virtual ~Sensor() = default;

    void calibrate(double offset) {
        calibrationOffset = offset;
    }

    virtual double getReading() = 0;

    std::string getID() const { return sensorID; }
};

class TemperatureSensor : public Sensor {
public:
    using Sensor::Sensor;

    double getReading() override {
        value = 22.5 + calibrationOffset;
        lastUpdate.timestamp = std::time(nullptr);

        if (value > 50.0) {
            std::cout << "[ALERT] Sensor " << sensorID << ": High Temperature! " << value << "\n";
        }
        return value;
    }
};

class MonitoringSystem {
private:
    std::vector<Sensor*> sensors;
    StatisticsCollector collector;

public:
    void addSensor(Sensor* s) {
        sensors.push_back(s);
    }

    void updateAll() {
        for (auto sensor : sensors) {
            double val = sensor->getReading();
            collector.addData(sensor->getID(), val);
        }
    }

    const StatisticsCollector& getStats() const { return collector; }
};
