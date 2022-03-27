#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mu;
int count = 1;
condition_variable cv;

void PrintOdd()	// fungsi untuk mengeprint angka ganjil
{
	for (int count = 1; count <= 10; count++)	//looping angka ganjil
	{
		unique_lock<mutex> locker(mu);
		// Kondisi untuk ganjil
		if (count % 2 == 1)				
		{
			cout << count << endl;	

			// fungsi untuk mendelay selama 1 detik 
			this_thread::sleep_for(chrono::seconds(1));				
		}
	}
	cout << "Ganjil Selesai " << endl;

}

// Fungsi untuk mengeprint angka genap
void PrintEven()	
{
	//Looping angka genap
	for (int count = 1; count <= 10; count++)	
	{
		//Mengkondisikan angka genap
		if (count % 2 == 0)				
		{
			cout << count << endl;

			// Fungsi untuk mendelay selama 2.5 detik
			this_thread::sleep_for(chrono::milliseconds(2500));		
		}
	}
	cout << "Genap Selesai" << endl;
}

/*		//Nyoba --salah
void PrintEven()
{
	for (; count < 10;)
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, []() { return (count % 2 == 0); });
		std::cout << "From Even: " << count << std::endl;
		count++;
		locker.unlock();
		cond.notify_all();
	}
}*/

int main()
{
	// Memulai thread odd
	thread th1(PrintOdd);

	// Memulai thread even
	thread th2(PrintEven);

	// Menunggu thread odd untuk selesai
	th1.join();				
	// Menunggu thread even untuk selesai
	th2.join();				


	return 0;
}
