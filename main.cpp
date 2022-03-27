#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


std::mutex mu;          //Pendeklarasian Mutex
std::condition_variable cond;          //
int count;

//Fungsi untuk mengeprint angka ganjil
void PrintOdd()
{
    for (count = 0; count < 10; count++)
    {
        if (count % 2 == 1)
        {
            //Digunakan karena menggunakan condition_variable
	    //Menunggu sampai main() untuk mengirim data
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, []() { return (count % 2 == 1); });

	    //Data terkirim, lock sudah dimiliki
            std::cout << count << std::endl;

	    //Fungsi untuk mendelay selama 1 detik
            std::this_thread::sleep_for(std::chrono::seconds(1));

            locker.unlock();       //Unlock the Mutex
            cond.notify_all();     //Notify PrintEven that is done
        }
    }
    std::cout << "Angka Ganjil Selesai" << std::endl;
}

//Fungsi untuk mengeprint angka genap
void PrintEven()
{
    for (count = 0; count < 10; count++)
    {
        if (count % 2 == 0)
        {
	    //menunggu sampai main() untuk mengirim data
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, []() { return (count % 2 == 0); });
            std::cout << count << std::endl;

	    //Fungsi untuk mendelay selama 2,5 detik / 2500 milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            locker.unlock();    //Unlock the Mutex
            cond.notify_all();  //Notify PrintEven that is done
        }
    }
    std::cout << "Angka genap Selesai";
}

int main()
{
    //Spawn new thread that calls PrintOdd
    std::thread t1(PrintOdd);
		
    //Spawn new thread that calls PrintEven
    std::thread t2(PrintEven);

    //Synchronize threads
    t1.join();          //Pauses until first finishes
    t2.join();          //Pauses until first finishes

    return 0;
}
