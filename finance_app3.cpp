//Topic - Finance Application using Priority Queue and Stack
//Priority Queue using Singly Linked List
//Stack using Doubly Linked List

#include<iostream>
using namespace std;

int pin = 4102; //For security authentication during payment

class Date //for storing Date of bill payment
{
    int day;
    int month;
    int year;
    public:
    friend class pending_bill; 
    friend class pending_bills_priority_queue; 
    friend class transaction_history;
    bool isEarlier(Date date1, Date date2); 
};

bool Date::isEarlier(Date date1, Date date2) //function for comparing two dates
{
    if (date1.year != date2.year) {
        return date1.year > date2.year;
    }
    if (date1.month != date2.month) {
        return date1.month > date2.month;
    }
    return date1.day > date2.day;
}

class pending_bill  //pending_bill node for linked list
{
    string bill_name,payment_method;
    float amount;
    Date due_date,payment_date;
    pending_bill *next,*previous;
    public:
    pending_bill(string bill,float amt,int day,int month,int year);
    friend class pending_bills_priority_queue;
    friend class transaction_history;
};

pending_bill::pending_bill(string bill,float amt,int day,int month,int year)
{
    bill_name = bill;
    amount = amt;
    due_date.day = day;
    due_date.month = month;
    due_date.year = year;
    next = NULL;
    previous = NULL;
}

class transaction_history  //For storing Transaction History of Payments in stack using Doubly Linked List
{
    pending_bill *top;
    public:
    transaction_history();
    void push(pending_bill *temp);
    void display_history();
};

transaction_history::transaction_history()
{
    top = NULL;
}

void transaction_history::push(pending_bill *temp)
{
    if(top==NULL)
    {
        top = temp;
    }
    else
    {
        top->next = temp;
        temp->previous = top;
        top = temp;
    }
}

void transaction_history::display_history() //For displaying Transaction History
{
    if(top==NULL)
    {
        cout<<"Transaction History is Empty!"<<endl;
    }
    else
    {
        pending_bill *temp = top;
        int i = 1;

        cout<<"Transaction History:-\n"<<endl;

        while(temp!=NULL)
        {
             cout<<i<<"."<<"Bill Name:"<<temp->bill_name<<endl;
             cout<<"  "<<"Amount:"<<temp->amount<<endl;
             cout<<"  "<<"Payment Method:"<<temp->payment_method<<endl;
             cout<<"  "<<"Payment Completed on:"<<temp->payment_date.day<<"-"<<temp->payment_date.month<<"-"<<temp->payment_date.year<<endl;
             cout<<""<<endl;

             i++;
             temp = temp->previous;
        }
    }
}

class pending_bills_priority_queue  //Priority Queue for storing pending bills using Singly Linked List
{
   pending_bill *front,*rear;
   int count;
   public:
   pending_bills_priority_queue();
   void enqueue_pending_bill();
   void dequeue_pending_bill(transaction_history &t);
   void display_queue();
   void complete_bill_payment();
};

pending_bills_priority_queue::pending_bills_priority_queue()
{
    front = rear = NULL;
    count = 0;
}

void pending_bills_priority_queue::enqueue_pending_bill() //Adding Bill to the priority Queue
{
    string bill_name;
    float amount;
    int day,month,year;

    if(front==NULL && rear==NULL)
    {
        cout<<"Enter Name of Bill:";
        cin>>bill_name;
        cout<<"Enter Amount of Bill:";
        cin>>amount;
        cout<<"Enter Due Date of Bill(Date Month Year):";
        cin>>day>>month>>year;

        pending_bill *nb = new pending_bill(bill_name,amount,day,month,year);
        front = rear = nb;

        cout<<"Bill Added Successfully!"<<endl;
        count++;
    }
    else if(count==10)
    {
        cout<<"Cannot Add Bill , Queue is Full!"<<endl;
    }
    else
    {
        cout<<"Enter Name of Bill:";
        cin>>bill_name;
        cout<<"Enter Amount of Bill:";
        cin>>amount;
        cout<<"Enter Due Date of Bill(Date Month Year):";
        cin>>day>>month>>year;

        pending_bill *nb = new pending_bill(bill_name,amount,day,month,year);
        pending_bill *temp = front;
        Date d;

        while(temp!=NULL)
        {
            if(d.isEarlier(temp->due_date,nb->due_date) && temp==front)
            {
                 nb->next = front;
                 front = nb;

                 cout<<"Bill Added Successfully!"<<endl;
                 count++;

                 return;
            }
            else if(d.isEarlier(temp->due_date,nb->due_date) && temp!=front)
            {
                pending_bill *t = front;

                while(t->next!=temp)
                {
                    t = t->next;
                }

                nb->next = temp;
                t->next = nb;

                cout<<"Bill Added Successfully!"<<endl;
                count++;

                return;
            }

            temp = temp->next;
        }

        rear->next = nb;
        rear = nb;

        cout<<"Bill Added Successfully!"<<endl;
        count++;
    }
}

void pending_bills_priority_queue::dequeue_pending_bill(transaction_history &t)
{
    if(front==NULL && rear==NULL)
    {
        cout<<"Cannot Complete Payment , No Pending Bills in Queue!"<<endl;
    }
    else if(front==rear)
    {
        complete_bill_payment();

        t.push(front);

        front = rear = NULL;
        count--;

        cout<<"\nPayment Completed Successfully!"<<endl;
    }
    else
    {
        complete_bill_payment();

        t.push(front);

        front = front->next;
        count--;

        cout<<"\nPayment Completed Successfully!"<<endl;
    }
}

void pending_bills_priority_queue::display_queue()
{
    if(front==NULL && rear==NULL)
    {
        cout<<"No Pending Bills In Queue!"<<endl;
    }
    else 
    {
        pending_bill *temp = front;
        int i = 1;

        cout<<"Your Pending Bills:-\n"<<endl;

        while(temp!=NULL)
        {
             cout<<i<<"."<<"Name:"<<temp->bill_name<<endl;
             cout<<"  "<<"Amount:"<<temp->amount<<endl;
             cout<<"  "<<"Due Date:"<<temp->due_date.day<<"-"<<temp->due_date.month<<"-"<<temp->due_date.year<<endl;
             cout<<""<<endl;

             i++;
             temp = temp->next;
        }
    }
}

void pending_bills_priority_queue::complete_bill_payment()
{
        int choose,take_pin;
        Date d;

        cout<<"Bill Payment to be done:-\n"<<endl;
        cout<<"Name:"<<front->bill_name<<endl;
        cout<<"Amount:"<<front->amount<<endl;
        cout<<"Due Date:"<<front->due_date.day<<"-"<<front->due_date.month<<"-"<<front->due_date.year<<"\n"<<endl;
        cout<<"Enter today's Date(Date Month Year):";
        cin>>d.day>>d.month>>d.year;

        if(d.isEarlier(d,front->due_date))
        {
            float fine = 0.10 * front->amount;
            float amount = front->amount;
            front->amount = front->amount + fine;
            cout<<"\nDue Date has passed already , a 10% fine will be imposed"<<endl;
            cout<<"Your new Bill Amount is "<<amount<<" + "<<fine<<" = "<<front->amount<<endl;
        }

        cout<<"\n";

        do
        {

        cout<<"1.Credit Card\n2.Debit Card\n3.NetBanking\n4.UPI\n"<<endl;
        cout<<"Select Any Payment Method:";
        cin>>choose;

      while(true)
      {
        cout<<"\nEnter Payment Pin:";
        cin>>take_pin;

        if(take_pin==pin)
        {
            switch(choose)
            {
                case 1:
                  front->payment_method = "Credit Card";
                  break;
                case 2:
                  front->payment_method = "Debit Card";
                  break;
                case 3:
                  front->payment_method = "NetBanking";
                  break;
                case 4:
                  front->payment_method = "UPI";
                  break;
                default:
                  cout<<"Invalid Choice!\n"<<endl;
                  break;
            }

            break;
        }
        else
        {
            cout<<"\nPayment Failed , Wrong Pin , Please Re-enter Pin again!"<<endl;
        }
      }

        }while(choose>4 || choose<1);

        front->payment_date = d;
}
         
int main()
{
    int choose;
    pending_bills_priority_queue p;
    transaction_history t;

    do
    {
       cout<<"\n\n\n\n------------------/*  Main Menu of Finance App  *\\------------------"<<endl;
       cout<<"\n"<<endl;
       cout<<"\n1.Add Pending Bill\n2.Complete Bill Payment\n3.Show Pending Bills Queue\n4.Show Transaction History\n5.Exit\n"<<endl;
       cout<<"Select Any:";
       cin>>choose;

       cout<<"\n"<<endl;

       switch(choose)
       {
           case 1:
             p.enqueue_pending_bill();
             break;
           case 2:
             p.dequeue_pending_bill(t);
             break;
           case 3:
             p.display_queue();
             break;
           case 4:
             t.display_history();
             break;
           case 5:
             break;
           case 6:
             cout<<"Invalid Choice!"<<endl;
             break;      
       }

    }while(choose!=5);
            
    return 0;
}