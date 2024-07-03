#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// �������ṹ�壬�����������Ĵ��䷶Χ��˵�L���Ҷ˵�R�����贫��ʱ��t
struct Sensor {
    double L, R, t;
};

// �ȽϺ��������ڰ��մ��������Ҷ˵�R��������
bool compare(Sensor a, Sensor b) {
    return a.R < b.R;
}

int main() {
    int T;
    cin >> T; // ��ȡ��������T
    while (T--) {
        int n;
        double D;
        cin >> n >> D; // ��ȡ����������n���յ�D
        vector<Sensor> sensors(n);
        for (int i = 0; i < n; ++i) {
            cin >> sensors[i].L >> sensors[i].R >> sensors[i].t; // ��ȡÿ������������Ϣ
        }

        // �����������Ҷ˵�R��������
        sort(sensors.begin(), sensors.end(), compare);

        vector<double> x_points; // �洢�ٶȱ仯��λ��
        vector<double> speeds; // �洢��Ӧ������ٶ�

        double current_x = 0; // ��ǰ���˻���λ��

        for (int i = 0; i < n; ++i) {
            double L = sensors[i].L;
            double R = sensors[i].R;
            double t = sensors[i].t;

            if (current_x < L) {
                // �����ǰ���˻�λ���ڴ������Ĵ��䷶Χ��࣬���ȷɵ��������Ĵ��䷶Χ���
                x_points.push_back(L);
                speeds.push_back(14.99); // ����14.99 m/s����������ٶ�
                current_x = L;
            }

            // �����յ��غϵ���ʼ�㲻�غϵĴ���������
            double total_time = t;
            int j = i + 1;
            while (j < n && sensors[j].R == R) {
                total_time += sensors[j].t;
                j++;
            }
            i = j - 1; // ����i���������غϴ�������λ��

            double flight_distance = R - current_x; // ��Ҫ���еľ���
            double required_speed = flight_distance / total_time; // ���������ٶ�
            x_points.push_back(R);
            speeds.push_back(required_speed);
            current_x = R; // ���µ�ǰ���˻�λ��
        }

        if (current_x < D) {
            // ������һ���������Ľ�������Ȼû�е��յ�D������ξ���Ҳ��û�д���������������
            x_points.push_back(D);
            speeds.push_back(14.99); // ������ٶȷ��е��յ�
        }

        cout << x_points.size() << endl; // ����ٶȱ仯����
        for (double x : x_points) {
            cout << fixed << setprecision(7) << x << " "; // ����ٶȱ仯��λ��
        }
        cout << endl;
        for (double v : speeds) {
            cout << fixed << setprecision(7) << v << " "; // �����Ӧ������ٶ�
        }
        cout << endl;
    }

    return 0;
}