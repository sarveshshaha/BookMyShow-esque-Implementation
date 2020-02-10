#include<iostream>
#include<string.h>

using namespace std;

class Seat
{
	private:
	int seat_no;
	Seat* next;
	Seat* previous;

	public:
	void setSeat(int);
	void setnext();
	void setnext(Seat*);
	void setprevious();
	void setprevious(Seat*);

	int getSeat();
	Seat* getnext();
	Seat* getprevious();
};

void Seat :: setSeat(int r)
{
	seat_no=r;
}

void Seat :: setnext()
{
	next=new Seat;
}

void Seat :: setnext(Seat* n)
{
	next=n;
}

void Seat :: setprevious()
{
	previous=new Seat;
}

void Seat :: setprevious(Seat* p)
{
	previous=p;
}

int Seat :: getSeat()
{
	return seat_no;
}

Seat* Seat :: getnext()
{
	return next;
}

Seat* Seat :: getprevious()
{
	return previous;
}

class Row
{
	public:
	Seat* start=NULL;
	Seat* temp=NULL;
	Seat* ptr=NULL;
	int count=0;

	public:
	void bookSeats();
	void displaySeats(int);
	void sortSeats();
	void cancelSeats();
};

void Row :: bookSeats()
{
	int no,check=0,op=0;
	Seat* traverse;

	whenstartisstillnull:if(start==NULL)
	{
		cout<<"\nEnter The Seat Number : \n";
		cin>>no;

		if(no<8)
		{
			start=new Seat;
			temp=start;
			ptr=start;
			temp->setSeat(no);
			temp->setnext(temp);
			temp->setprevious(temp);
			count++;
		}
		else
		{
			cout<<"\nThere Are Only 7 Total Seats !!!\n";
			goto whenstartisstillnull;
		}
	}

	do
	{
		cout<<"\nDo You Want To Book One More Seat ?\n0 : No\n1 : Yes\n";
		cin>>op;

		if(op==1)
		{
			if(count<8)
			{
				cout<<"\nEnter The Seat Number : \n";
				cin>>no;

				if(no<8)
				{
					traverse=start;
					check=0;

					for(int i=0;i<count;i++)
					{
						if(no!=traverse->getSeat())
						{
							check++;
						}

						traverse=traverse->getnext();
					}

					if(check==count)
					{
						/*if(temp->getSeat()<no)
						{*/
							temp->setnext();
							temp=temp->getnext();
							temp->setSeat(no);
							temp->setprevious(ptr);
							start->setprevious(temp);
							ptr=temp;
							temp->setnext(start);
							count++;
						//}
						/*else if(temp->getSeat()>no)
						{
							ptr=temp;
							traverse=temp;
							temp->setnext();
							traverse=temp->getnext();
							traverse->setSeat(temp->getSeat());
							temp->setSeat(no);
							temp=traverse;
							temp->setprevious(ptr);
							start->setprevious(temp);
							count++;
						}*/
					}
					else
					{
						cout<<"\nThe Seat Is Already Booked !!!\n";
					}
				}
				else
				{
					cout<<"\nThere Are Only 7 Total Seats !!!\n";
				}
			}
			else
			{
				cout<<"\nAll Seats Are Booked !!!\n";
				break;
			}
		}
	}while(op==1);
}

void Row :: displaySeats(int rno)
{
	Seat* traverse;

	if(start==NULL)
	{
		cout<<"\n";
		cout<<rno+1<<"\t";
		for(int i=0;i<7;i++)
		{
			cout<<"F\t";
		}

		cout<<"\n";
	}
	else
	{
		traverse=start;
		int ch=0,t=0,cnt=0;

		cout<<"\n";

		for(int i=0;i<count;i++)
		{/*
			cout<<traverse->getSeat()<<"\t";
			traverse=traverse->getnext();
		 */

			t=traverse->getSeat();

			if(traverse==start)
			{
				cout<<rno+1<<"\t";
				t=traverse->getSeat();
				ch=t-1;
				for(int i=0;i<ch;i++)
				{
					cout<<"F\t";
					cnt++;
				}
				cout<<t<<"\t";
				cnt++;
				traverse=traverse->getnext();
			}
			else
			{
				t=traverse->getSeat();
				ch=t-traverse->getprevious()->getSeat();
				for(int i=0;i<ch-1;i++)
				{
					cout<<"F\t";
					cnt++;
				}
				cout<<t<<"\t";
				cnt++;
				traverse=traverse->getnext();
			}
		}

		for(int i=0;i<(7-cnt);i++)
		{
			cout<<"F\t";
		}

		cout<<"\n";
	}
}

void Row :: sortSeats()
{
	Seat* traverse1;
	Seat* traverse2;
	int tseat=0;

	traverse1=start;

	for(int i=0;i<count;i++)
	{
		traverse2=start;

		for(int j=0;j<count;j++)
		{
			if(traverse1->getSeat()<traverse2->getSeat())
			{
				tseat=traverse1->getSeat();
				traverse1->setSeat(traverse2->getSeat());
				traverse2->setSeat(tseat);
			}

			traverse2=traverse2->getnext();
		}

		traverse1=traverse1->getnext();
	}
}

void Row :: cancelSeats()
{
	Seat* traverse;
	int cseat=0,op=0;

	do
	{
		int check=0;

		traverse=start;

		if(start!=NULL)
		{
			cout<<"\nEnter The Seat Number Which You Want To Cancel The Booking Of : \n";
			cin>>cseat;

			for(int i=0;i<count;i++)
			{
				if(cseat==traverse->getSeat())
				{
					check=1;
					break;
				}

				traverse=traverse->getnext();
			}

			if(check==1)
			{
				if(temp==traverse)
				{
					temp=temp->getprevious();
					ptr=ptr->getprevious();
				}

				if(start==traverse)
				{
					start=start->getnext();
				}

				traverse->getprevious()->setnext(traverse->getnext());
				traverse->getnext()->setprevious(traverse->getprevious());
				count--;

				cout<<"\nThe Seat Is Deleted !!!\n";
			}
			else
			{
				cout<<"\nThe Seat Has Not Yet Been Booked !!!\n";
			}
		}
		else
		{
			cout<<"\nThis Row Has Not Got Even A Single Seat Booked !!!\n";
		}

		cout<<"\nDo You Want To Cancel Another Seat From This Row ?\n1 : Yes\n0 : No\n";
		cin>>op;
	}while(op==1);

	if(count==0)
	{
		start=NULL;
	}
}

int main()
{
	Row r[10];
	int op=0,rno=0,op2=0;

	cout<<"\nWELCOME TO CINEMAX THEATER !!!\n";
	cout<<"\nThere Are Total 10 Rows And 7 Seats In Each Row In This Theater !!!\n";
	cout<<"\nAs There Are No Bookings Made Yet, This Is How The Theater Looks :\n";

	cout<<"\n\t";
	for(int i=0;i<7;i++)
	{
		cout<<i+1<<"\t";
	}
	cout<<"\n";
	for(int i=0;i<10;i++)
	{
		r[i].displaySeats(i);
	}

	cout<<"\nF : Free Seats, Number : Number Of The Seat Which Has Been Already Booked !!!\n";

	do
	{
		cout<<"\nWhich Operation Do You Want To Perform ?\n1 : Display Seats\n2 : Book Seats\n3 : Cancel Seats\n4 : Finalize Bookings\n";
		cin>>op;

		switch(op)
		{
			case 1:
			cout<<"\n\t";
			for(int i=0;i<7;i++)
			{
				cout<<i+1<<"\t";
			}
			cout<<"\n";

			for(int i=0;i<10;i++)
			{
				r[i].displaySeats(i);
			}
			break;

			case 2:
			do
			{
				cout<<"\nIn Which Row Do You Want To Book The Seats ?\n1-10\n";
				cin>>rno;
				if(rno<=10)
				{
					r[rno-1].bookSeats();
					r[rno-1].sortSeats();
				}

				cout<<"\nDo You Want To Book Seats Form Another Row ?\n1 : Yes\n0 : No\n";
				cin>>op2;
			}while(op2==1);
			break;

			case 3:
			do
			{
				cout<<"\nIn Which Row Do You Want To Cancel The Seats ?\n1-10\n";
				cin>>rno;
				if(rno<=10)
				{
					r[rno-1].cancelSeats();
					r[rno-1].sortSeats();
				}

				cout<<"\nDo You Want To Cancel Seats Form Another Row ?\n1 : Yes\n0 : No\n";
				cin>>op2;
			}while(op2==1);
			break;

			case 4:
			cout<<"\nThe Seats Have Been Finalized, The Finalized Seats Are : \n";
			cout<<"\n\t";
			for(int i=0;i<7;i++)
			{
				cout<<i+1<<"\t";
			}
			cout<<"\n";

			for(int i=0;i<10;i++)
			{
				r[i].displaySeats(i);
			}
			cout<<"\nThe Show Will Start Very Soon,Thank You For Visiting Cinemax Theater !!!\n";
			break;
		}
	}while(op!=4);

	return 0;
}
