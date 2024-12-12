#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class test
{
private:
	int n, m; //����� ��������� � ����� �����������
    vector<vector<int>> A; 
	int size; //����������� ������� nxm
	int k; //����� ��������� ����������
public:
	void input(string name)
	{
		ifstream input(name);
        input >> n >> m;

		size = n + m;

		A.resize(size);
		for (int i = 0; i < size; i++)
			A[i].resize(m + 1);

		for (int i = 0; i < n; i++){
			for (int j = 0; j < m + 1; j++) {
                input >> A[i][j];
			}
			A[i][m] *= -1;
		}
        input.close();

		for (int i = n, j = 0; i < size; i++, j++)
			A[i][j] = 1;
	}

	bool SLAE()
	{
        //�������� ������� � ������� ������������ ����
        for (int i = 0; i < n; i++){
            bool row_done = false;

            while (!row_done){
                //���� ����������� ������� � ������
                bool finded = false;
                int min_value = 0;
                for (int j = i; j < m; j++){
                    if (!finded){
                        if (A[i][j] != 0){
                            min_value = j;
                            finded = true;
                        }
                    }
                    else
                    {
                        if (abs(A[i][j]) < abs(A[i][min_value]) && A[i][j] != 0)
                            min_value = j;
                    }
                }

                if (!finded && A[i][m] == 0){
                    A.erase(A.begin() + i);
                    i--;
                    n--;
                    size--;
                    continue;
                }

                if (finded){
                    //�������� ������� � ����������� ��������� �� ���������
                    for (int j = i; j < m; j++){
                        if (j != min_value && A[i][j] != 0){
                            int q = A[i][j] / A[i][min_value];
                            for (int k = i; k < A.size(); k++)
                                A[k][j] -= A[k][min_value] * q;
                        }
                    }

                    //���� ������������ ������� ���������,�� ������ ��� ������� � �������
                    if (A[i][i] == 0){
                        for (int k = i; k < size; k++){
                            swap(A[k][i], A[k][min_value]);
                        }
                    }
                }

                //��������� ��� �������������� �������� �� ������� ���������
                bool in_diag = false;
                for (int j = i + 1; j < m; j++){
                    if (A[i][j] != 0){
                        in_diag = true;
                        break;
                    }
                }

                //���� ����� �� �������, ��������� ������ ����� �� ������� �� ���� � ������������� �������� � � ���� ���� ������ �������
                if (!in_diag){
                    if (A[i][i] != 0){
                        if (A[i][m] % A[i][i] != 0){
                            return false;
                        }
                        else
                        {
                            int q = A[i][m] / A[i][i];
                            for (int k = i; k < A.size(); k++)
                                A[k][m] -= A[k][i] * q;
                        }
                    }
                    else
                    {
                        return false;
                    }

                    if (A[i][i] == 1){
                        int q = A[i][m];
                        for (int k = i; k < A.size(); k++)
                            A[k][m] -= A[k][i] * q;
                    }
                    //���� ������ ����� �������, ����������� ��������� ������
                    if (A[i][m] == 0)
                        row_done = true;
                }
            }
        }
        return true;
	}

	void output(string out, bool flag)
	{
		ofstream output(out);
        k = m - n;

        //���� ����� ��������� ���������� ����� < 0, �� ���� �������
        if (k < 0)
            flag = false;

        if (!flag) {
            output << "NO SOLUTIONS";
		}
		else
		{
			output << k << endl;

            for (int i = n; i < size; i++) {
                for (int j = m - k; j < m + 1; j++){
                    output << A[i][j] << " ";
                }
                output << std::endl;
            }
		}
		output.close();
	}
};

int main() {
	
	test ss;

	ss.input("input.txt");
    bool flag = ss.SLAE();
	ss.output("output.txt",flag);
}