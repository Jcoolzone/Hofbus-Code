#include <pthread.h>
struct station {
    int Free_Seats;
    int Students_Waiting;
    int Student_Order; 
    pthread_mutex_t lock; 
    pthread_cond_t Student_Cond;
    pthread_cond_t Bus_Cond; 
     
    
};

void
station_init(struct station *station)
{
    station->Free_Seats = 0;
    station->Students_Waiting = 0; 
    station->Student_Order = 1; 
    pthread_mutex_init(&station->lock, NULL); 
    pthread_cond_init(&station->Student_Cond, NULL);  
    pthread_cond_init(&station->Bus_Cond, NULL); 
}


void
station_load_bus(struct station *station, int count)
{
    pthread_mutex_lock(&station->lock);
    station->Free_Seats = count;
    pthread_cond_broadcast(&station->Student_Cond);
    while(station->Students_Waiting > 0 && station->Free_Seats > 0) {
        pthread_cond_wait(&station->Bus_Cond,&station->lock);
    }
    station->Free_Seats = 0;
    pthread_mutex_unlock(&station->lock);
}

int
station_wait_for_bus(struct station *station, int myticket, int myid)
{
     pthread_mutex_lock(&station->lock);
     station->Students_Waiting++;
     while(station->Free_Seats == 0 || myticket != station->Student_Order){
        pthread_cond_wait(&station->Student_Cond, &station->lock);
     }
     station->Free_Seats--;
     station->Students_Waiting--;
     int turn = station->Student_Order;
     station->Student_Order++;
     pthread_cond_signal(&station->Bus_Cond);
     pthread_cond_broadcast(&station->Student_Cond);
     pthread_mutex_unlock(&station->lock);
     return turn;	
} 
