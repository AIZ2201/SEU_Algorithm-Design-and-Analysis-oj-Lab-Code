#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 传感器结构体，包含传感器的传输范围左端点L、右端点R和所需传输时间t
struct Sensor {
    double L, R, t;
};

// 比较函数，用于按照传感器的右端点R进行排序
bool compare(Sensor a, Sensor b) {
    return a.R < b.R;
}

int main() {
    int T;
    cin >> T; // 读取数据组数T
    while (T--) {
        int n;
        double D;
        cin >> n >> D; // 读取传感器数量n和终点D
        vector<Sensor> sensors(n);
        for (int i = 0; i < n; ++i) {
            cin >> sensors[i].L >> sensors[i].R >> sensors[i].t; // 读取每个传感器的信息
        }

        // 按传感器的右端点R进行排序
        sort(sensors.begin(), sensors.end(), compare);

        vector<double> x_points; // 存储速度变化的位置
        vector<double> speeds; // 存储对应区间的速度

        double current_x = 0; // 当前无人机的位置

        for (int i = 0; i < n; ++i) {
            double L = sensors[i].L;
            double R = sensors[i].R;
            double t = sensors[i].t;

            if (current_x < L) {
                // 如果当前无人机位置在传感器的传输范围左侧，则先飞到传感器的传输范围起点
                x_points.push_back(L);
                speeds.push_back(14.99); // 假设14.99 m/s是最大允许速度
                current_x = L;
            }

            // 处理终点重合但起始点不重合的传感器区间
            double total_time = t;
            int j = i + 1;
            while (j < n && sensors[j].R == R) {
                total_time += sensors[j].t;
                j++;
            }
            i = j - 1; // 更新i到处理完重合传感器的位置

            double flight_distance = R - current_x; // 需要飞行的距离
            double required_speed = flight_distance / total_time; // 计算所需速度
            x_points.push_back(R);
            speeds.push_back(required_speed);
            current_x = R; // 更新当前无人机位置
        }

        if (current_x < D) {
            // 如果最后一个传感器的结束点仍然没有到终点D，则这段距离也是没有传感器的自由区域
            x_points.push_back(D);
            speeds.push_back(14.99); // 以最大速度飞行到终点
        }

        cout << x_points.size() << endl; // 输出速度变化次数
        for (double x : x_points) {
            cout << fixed << setprecision(7) << x << " "; // 输出速度变化的位置
        }
        cout << endl;
        for (double v : speeds) {
            cout << fixed << setprecision(7) << v << " "; // 输出对应区间的速度
        }
        cout << endl;
    }

    return 0;
}