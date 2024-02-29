#include<iostream>
#include<cmath>
#include<string>
#include<random>


using namespace std;

class Nde
{
    public:
    int cnic, seatnmbr, seat, penalty;
    string name,ctgory;
    Nde *nxt, *prev; //if pointer to nxt added in below class, then pointers of those class wont contain *nxt in them which is required.
};//how to traverse *prev in nodes?? ?
class AcrftLnLst
{
    public:
    Nde *Hd_BusinesClas, *Hd_EconmClas;
    
    AcrftLnLst()
    {Hd_BusinesClas=NULL;
    Hd_EconmClas=NULL;}

    AcrftLnLst(char book)
    {
        Nde *currNde, *prevv;//=new Nde();
        //small aircraft
        if(book=='S')//singlEngined_plane
        {
            Hd_BusinesClas=new Nde();
            currNde=prevv=Hd_BusinesClas;
            for(int rc=1; rc<=30; rc++)
            {    
                currNde->seatnmbr=rc;
                currNde->ctgory="Business";
                currNde->nxt=new Nde();
                prevv=currNde;
                currNde=currNde->nxt;
            }
            prevv->nxt=NULL;
            currNde=NULL;
            delete currNde;

            Hd_EconmClas=new Nde();
            currNde=Hd_EconmClas;
            for(int rc=31; rc<=100; rc++)
            {
                currNde->seatnmbr=rc;
                currNde->ctgory="Economy";
                currNde->nxt=new Nde();
                prevv=currNde;
                currNde=currNde->nxt;
            }
            prevv->nxt=NULL;
            currNde=NULL;   //currNde->prev=prevNd...?? how define them to move around?
            delete currNde;//so that the additional node created at loop's end deletes.
        }
        else if(book=='D')//char cant store more than 1 letter.
        {
            Hd_BusinesClas=new Nde();
            currNde=Hd_BusinesClas;
            for(int rc=1; rc<=50; rc++)
            {    
                currNde->seatnmbr=rc;
                currNde->ctgory="Business";
                currNde->nxt=new Nde();
                prevv=currNde;
                currNde=currNde->nxt;
            }
            prevv->nxt=NULL;
            currNde=NULL;
            delete currNde;

            Hd_EconmClas=new Nde();
            currNde=Hd_EconmClas;
            for(int rc=51; rc<=150; rc++)
            {
                currNde->seatnmbr=rc;
                currNde->ctgory="Economy";
                currNde->nxt=new Nde();
                prevv=currNde;
                currNde=currNde->nxt;
            }
            prevv->nxt=NULL;
            currNde=NULL;   //currNde->prev=prevNd...?? how define them to move around?
            delete currNde;
        }
        else
        {
            std::cout<<"....\tPlane Category Unavailable! ..#\n";
            }
    }


    bool EmptyArcrf_bookngDD(/*int TotBC, int TotEC*/)//Big plane empty all seat nodes by cancelling bookings
    {
        Nde *curNd=Hd_BusinesClas;
   while(curNd)//     for(int dlB=1; dlB<=TotBC; dlB++)         //scope of dlB ends when the loop ends so it can be redlared elsewhere or in another loop.
        {//but if dlB has been declared previousely and tried to be declared in for loop, error will come.
           /*AcrftLnLst::*/DeletSpecfNdets_BC(curNd->cnic);
           curNd=curNd->nxt;
        } //delete curNd;
           
        /*Nde **/curNd=Hd_EconmClas;//curNd not to be declared again, only asignment to another node is enough.
        while(curNd) //for(int dlE=TotBC+1; dlE<=TotEC; dlE++)
        {
           AcrftLnLst::DeletSpecfNdets_EC(curNd->cnic);//AcrftLnLst::curNd not possible inside as it wasnt globally declared but in function.
           curNd=curNd->nxt;
        } //delete curNd; // due to this it would delete the whole node itself including seatnmbr. We r required to just NULL the CNIC and name to cancel the booking
        return true;
    }
    bool EmptyArcrf_bookngSS(/*int TotBC, int TotEC*/)//small plane empty all seat nodes by cancelling bookings
    {
        Nde *curNd=Hd_BusinesClas;
        while (curNd)  //for(int dlB=1; dlB<=TotBC; dlB++)
        {
           AcrftLnLst::DeletSpecfNdets_BC(curNd->cnic);
           curNd=curNd->nxt;
        } 
           
        curNd=Hd_EconmClas;
        while(curNd)//for(int dlE=TotBC+1; dlE<=TotEC; dlE++)
        {
           AcrftLnLst::DeletSpecfNdets_EC(curNd->cnic);
           curNd=curNd->nxt;
        } //delete curNd;// due to this it would delete the whole node itself including seatnmbr. We r required to just NULL the CNIC and name to cancel the booking
        return true;
    }

    bool DeletSpecfNdets_BC(/*Nde *Hd_BusinesClas_Spec,*/ int nic)//no need for passing head as no need to ask user where to start but instead just from head.
    {
        Nde *currNde=Hd_BusinesClas;//start from head
     while(currNde->cnic!=nic && currNde->nxt!=NULL)//->nxt added to stop from memory leak.
     {
       currNde=currNde->nxt;
     }
        //if(fndNdeBC(currNde, nic)) {
        if(currNde->cnic==nic)//this we did it again as when last node before NULL will be approached, while loop will end and for last node, we added this comparative statement. 
        {currNde->name="";
        currNde->cnic=0;
        return true;}
        else
        {return false;}              //currNde->seat=0;}//seat is element inputted by user to book that nmbr.
        //return currNde; return Hd_BusinesClas_Spec;
     }    // as function is not recursive, empty details will be returned if return;
    bool DeletSpecfNdets_EC(/*Nde *AcrftLnLst::*Hd_EconmClas_Spec,*/ int nic)//dont pass head but some new defined pointer as we dont want head to change.
    {
        Nde *currNde=Hd_EconmClas;
        while(currNde->cnic!=nic && currNde->nxt!=NULL)//->nxt added to stop from memory leak.
       {
         currNde=currNde->nxt;
       }        
        if(currNde->cnic==nic)//this we did it again as when last node before NULL will be approached, while loop will end and for last node, we added this comparative statement.
        {currNde->name="";
        currNde->cnic=0;
        return true;}
        else
        {return false;}              //currNde->seat=0;}//seat is element inputted by user to book that nmbr.
       // return currNde; return Hd_EconmClas_Spec;//no need for returns as node deleted
    }

    Nde* InsrtNdeBC(int TotBC, int ndx, Nde *PrsnDets) // asigning passengerQ fronteer to BusiClass.
    {       //make Nde object and pass that in main()
        Nde *currNde;
        if(ndx<=TotBC && ndx>0)
        {
           currNde=Hd_BusinesClas;
           for(int cn=1;cn<ndx; cn++)
           {currNde=currNde->nxt;}
            
             if(currNde->cnic!=0)
              {std::cout<<"//. .#. This seat is already booked. Selecting some other seat....\n\n";
              InsrtNdeBC(TotBC, ((rand() % (TotBC))+1), PrsnDets);
              }//int *psngerQ::seatRenpt();}
             else
             {currNde->cnic=PrsnDets->cnic;
             currNde->name=PrsnDets->name;
           //  currNde->seat=PrsnDets->seat;
             std::cout<<"<<<The Seat have been SUCCESSFULLY allocated.>>>\n";}
        }
        else
         {std::cout<<"# Sorry! the seat doesn't exist for 'Business Class'. Kindly input any seat from 1-"<<TotBC<<" range.\n\n";
         InsrtNdeBC(TotBC, ((rand() % (TotBC))+1), PrsnDets); 
         }
        //psngerQ::seatRenpt();}
     return currNde;
     }

	 Nde* InsrtNdeEC(int TotBC, int TotEC, int ndx, Nde *PrsnDets) // asigning passengerQ fronteer to EconClass.
    { // Why not PsngerQ *PrsnDets above?? How Posiible? What differences??? ?
           Nde *currNde;
           if(ndx<=TotEC /*&& ndx>TotBC*/)
        {
            /*Nde */currNde=Hd_EconmClas; // change & and * adding multiple and seeing Errors..   Reasoning them>>> & enhancing knowledge./.
            for(int cn=1;cn<ndx; cn++)
            {currNde=currNde->nxt;}

                 if(currNde->cnic!=0)
                 {std::cout<<"//. .#. This seat is already booked. Choose some other seat....\n\n";
                //seatRenpt();}
                 InsrtNdeEC(TotBC, TotEC, (rand() % (TotEC-TotBC)+TotBC+1), PrsnDets);
                 }
            
                 else
                 {currNde->cnic=PrsnDets->cnic;
                 currNde->name=PrsnDets->name;
                // currNde->seat=PrsnDets->seat;
                 std::cout<<"<<<The Seat have been SUCCESSFULLY allocated.>>>\n";}
        }
         else
         {std::cout<<"# Sorry! the seat doesn't exist for 'Economy Class'. Kindly input any seat from 31-100 range.\n\n";
      //  seatRenpt();}
          InsrtNdeEC(TotBC, TotEC, (rand() % (TotEC-TotBC)+TotBC+1), PrsnDets);
         }
     return currNde;   
    }

    // AcrftLnLst(Nde *Hd_BusinesClas, psngerQ *frnt) // if Nde * not written with Hd_BusinesClas, via error??
    // {//asign the selected BC seat to front passenger
        
    // }
 
    // AcrftLnLst(Nde *Hd_EconmClas, psngerQ *frnt)
    // {
        
    // }

    int FndNdeBC(/*Nde *Hd_BusinesClas,*/ int nic)//i passed head thinking that head seat of that specific airc will be passed whereas actually, func of that specific obj automatically points to variables of that obj.
    {
      Nde *currNd=Hd_BusinesClas;
        if(currNd->seatnmbr)//for searching all the seats, else if ->cnic would be added, recursion would stop as soon as an empty unallocated seat would be encountered.
        {
          while(currNd && currNd->cnic!=nic)
                                             //{if(currNd->cnic!=nic)
             {/*FndNdeBC(Hd_BusinesClas->nxt, nic);*/
             currNd=currNd->nxt;}
             if(currNd==NULL)
               {cout<<"\n 🛩️🛩️|The entered CNIC has not booked any seat in this Airlplane/Flight 🛩️.\t";
               return 0;}//if not added this, a random int would be returned.
             else if(currNd->cnic==nic)
               {cout<<"\n 🛩️|The Seat Number corresponding to this CNIC is:\t";
               return currNd->seatnmbr;}
        }
        else
        {return 0;} //return 0;
    }	
    int FndNdeEC(/*Nde AcrftLnLst::*Hd_EconmClas,*/ int nic)//i passed head thinking that head seat of that specific airc will be passed whereas actually, func of that specific obj automatically points to variables of that obj.
    {
      Nde *currNd=Hd_EconmClas;
        if(currNd->seatnmbr)//for searching all the seats, else if ->cnic would be added, recursion would stop as soon as an empty unallocated seat would be encountered.
        {
          while(currNd && currNd->cnic!=nic)
                                             //{if(currNd->cnic!=nic)
             {/*FndNdeBC(Hd_BusinesClas->nxt, nic);*/
             currNd=currNd->nxt;}
             if(currNd==NULL)
               {cout<<"\n 🛩🛩|The entered CNIC has not booked any seat in this Airlplane/Flight 🛩.\n";
               return 0;}
             else if(currNd->cnic==nic)
               {cout<<"\n 🛩|The Seat Number corresponding to this CNIC is:\t";
               return currNd->seatnmbr;}
        }
        else
        {return 0;}
    }	
      //above function will do the same job as nicFound()
    // bool nicFound(Nde *currNde)
    // {
    //     if(currNde)
    //     {
    //         if(currNde->cnic!=PrsnDets->cnic);
    //         {nicFound(currNde->nxt);}
    //         else
    //         {return true;}
    //     }
    //     else
    //     {return false;}
    // }

    // bool NoDuplct_cNic()   WHAT IF ABOVE nicFound() RETURNS int and we WANT BELOW function to act depending on the return values of them??
    // {
    //     if(nicFound());
    //     {return true;}
    //     else
    //     {return false;}
    // }

    // AcrftLnLst Static_CreatNdes() // Nde Static_CreatNdes()
    // {
    //     j;
    // }

    void Displ_ALLSeats(/*Nde *AcrftLnLst *Hd_BusinesClas,*/ int sze,int BorE)//no need to pass Nde return as Head_BC is already member function.
    {
        //int storEm=storFul=0;
        //string seatingsEmpt;
        Nde *currNde;
      //  Nde *currNdeE=Hd_EconmClas;
        //int i,j=0;
        int alc=4;
        //std::cout<<"\t\t'--'EMPTY BUSINESS CLASS SEATS'--'\n\n";
            // if(book=='S')singl
            // {
    
        for(int st_BC=0; st_BC<sze; st_BC++)//if condition: st_BC'='<sze, then 1 time extra the last node prints.
        {  
                  if(st_BC==0)
                 {std::cout<<"\n\n\t\t'--'BUSINESS CLASS SEATS'--'\n\n\t\t";
                 currNde=Hd_BusinesClas;}
                  if(st_BC==BorE)//if BorE+1 instead, the node that separates BC and EC is printed on both of the classes.
                 {std::cout<<"\n\n\t\t'--'ECONOMY CLASS SEATS'--'\n\n\t\t";
                 currNde=Hd_EconmClas;}

            if(currNde->cnic==0)
            {
                cout<<"   '"<<currNde->seatnmbr<<"\t";
                if(alc%3==0)
                {std::cout<<endl<<"\t\t";
                alc=alc+1;}
                else
                {alc=alc+1;}
            }
            else if(currNde->cnic!=0)
            {
                cout<<"    "<<currNde->seatnmbr<<"\t";
                if(alc%3==0)
                {std::cout<<endl<<"\t\t";
                alc=alc+1;}
                else
                {
                alc=alc+1;}
            }

//currNde=Hd_EconmClas; //this will bring node to EC linklist as otherise, the currNde would be at NULL position after BC linklist ends.
        //   if(currNde->cnic==0)
        //   {std::cout<<currNde->seatnmbr<<"\t";          
        //      if(i%3==0)
        //      {std::cout<<endl;
        //      i=i+3;}
        //   }
        
              //seatingsEmpt/*[storEm]*/currNde->seatnmbr;
       //     storEm=storEm+1;                            //storEm++; seatingsEmpt[storEm]=' '; storEm++;
    
//           else if(currNde->cnic!=0)
//           {
//             if(st_BC==0)
//            {std::cout<<"\n\n\t\t'--'FULL/ASSIGNED BUSINESS CLASS SEATS'--'\n\n";}
//             if(st_BC>=BorE)
//            {std::cout<<"\n\n\t\t'--'FULL/ASSIGNED ECONOMY CLASS SEATS'--'\n\n";}
// //currNde=Hd_EconmClas;  //this will bring node to EC linklist as otherise, the currNde would be at NULL position after BC linklist ends.
//            std::cout<<currNde->seatnmbr<<"\t";
        
//            if(j%3==0)
//            {std::cout<<endl;
//            j=j+3;}

//           }
           if(currNde->nxt)
           {currNde=currNde->nxt;}
           
        }
           // seatingsFul[storFul]=currNde->seatnmbr;
            //storFul=storFul+1; //storFul++; seatingsFul[storFul]=' '; storFul++;
        //}
        //    cout<<"\t\t'--'EMPTY BUSINESS CLASS SEATS'--'\n\n";
        //     if(book='S')
        //     {
        //        for(int st_BC=0;st_BC<=29;)
               //{cout<<seatingsEmpt[st_BC]<<"  "<<seatingsEmpt[st_BC+1]<<"  "<<seatingsEmpt[st_BC+2]<<"\n";
               //st_BC=st_BC+3;}
        // cout<<"\n\n\t\t'--'EMPTY ECONOMY CLASS SEATS'--'\n\n";// as outside for loop, would print anyway so also operational for below for loop.
            //    for(int st_EC=30;st_EC<=99;)
            //    {cout<<seatingsEmpt[st_EC]<<"  "<<seatingsEmpt[st_EC+1]<<"  "<<seatingsEmpt[st_EC+2]<<"\n";
            //    st_EC=st_EC+3;}
            // }


            // else if (book='D')
            // {
            //    for(int st_BC=0;st_BC<=49;)
            //    {cout<<seatingsEmpt[st_BC]<<"  "<<seatingsEmpt[st_BC+1]<<"  "<<seatingsEmpt[st_BC+2]<<"\n";
            //    st_BC=st_BC+3;}

            //    for(int st_EC=50;st_EC<=149;)
            //    {cout<<seatingsEmpt[st_EC]<<"  "<<seatingsEmpt[st_EC+1]<<"  "<<seatingsEmpt[st_EC+2]<<"\n";
            //    st_EC=st_EC+3;}
            // }


        //     cout<<"\t\t'--'FULL/ASSIGNED BUSINESS CLASS SEATS'--'\n\n";
        //     if(book='singlEngined_plane')
        //     {
        //        for(int st_BC=1;st_BC<=30;)//CAN ALREADY DECLARED & used var be declared again and used in for loop??
        //        {cout<<seatingsFul[st_BC]<<"  "<<seatingsFul[st_BC+1]<<"  "<<seatingsFul[st_BC+2]<<"\n";
        //        st_BC=st_BC+3;}
        //    cout<<"\n\n\t\t'--'FULL/ASSIGNED ECONOMY CLASS SEATS'--'\n\n";
        //        for(int st_EC=31;st_EC<=100;)
        //        {cout<<seatingsFul[st_EC]<<"  "<<seatingsFul[st_EC+1]<<"  "<<seatingsFul[st_EC+2]<<"\n";
        //        st_EC=st_EC+3;}
        //     }
        //     else if (book='DoubleDecker')
        //     {
        //        for(int st_BC=1;st_BC<=50;)
        //        {cout<<seatingsFul[st_BC]<<"  "<<seatingsFul[st_BC+1]<<"  "<<seatingsFul[st_BC+2]<<"\n";
        //        st_BC=st_BC+3;}

        //        for(int st_EC=51;st_EC<=150;)
        //        {cout<<seatingsFul[st_EC]<<"  "<<seatingsFul[st_EC+1]<<"  "<<seatingsFul[st_EC+2]<<"\n";
        //        st_EC=st_EC+3;}
        //     }

            //else {cout<<"Error in Empty seats displaying.\n";}

        //else{cout<<"code error in DispAll_Seats() func.\n"}
    }


    // void Displ_AvlblSeats(Nde *Hd_BusinesClas, char unbook)
    // {
    //     int storEm = int storFul = 0;
    //     string seatingsFul;
    //     Nde *currNde=Hd_BusinesClas;
    //     if(currNde->cnic=0;)
    //     {
    //         seatingsEmpt[storEm]=currNde->seatnmbr;//if string is stored while after leaving unfilled spaces, does it put ' ' space in there or not???
    //         storEm=storEm+1; //storEm++; seatingsEmpt[storEm]=' '; storEm++;
    //     }
    //     else if(currNde->cnic!=0)
    //     {
    //         seatingsFul[storFul]=currNde->seatnmbr;
    //         storFul=storFul+1; //storFul++; seatingsFul[storFul]=' '; storFul++;
    //     }
    //        cout<<"\t\t'--'EMPTY BUSINESS CLASS SEATS'--'\n\n";
    //         if(book='singlEngined_plane')
    //         {
    //            for(int st_BC=0;st_BC<=30;)
    //            {cout<<seatingsEmpt[st_BC]<<"  "<<seatingsEmpt[st_BC+1]<<"  "<<seatingsEmpt[st_BC+2]<<"\n";
    //            st_BC=st_BC+3;}
    //        cout<<"\n\n\t\t'--'EMPTY ECONOMY CLASS SEATS'--'\n\n";
    //            for(int st_EC=31;st_EC<=100;)
    //            {cout<<seatingsEmpt[st_EC]<<"  "<<seatingsEmpt[st_EC+1]<<"  "<<seatingsEmpt[st_EC+2]<<"\n";
    //            st_EC=st_EC+3;}
    //         }
    //         else if (book='DoubleDecker')
    //         {
    //            for(int st_BC=0;st_BC<=50;)
    //            {cout<<seatingsEmpt[st_BC]<<"  "<<seatingsEmpt[st_BC+1]<<"  "<<seatingsEmpt[st_BC+2]<<"\n";
    //            st_BC=st_BC+3;}
    //       cout<<"\n\n\t\t'--'EMPTY ECONOMY CLASS SEATS'--'\n\n";
    //            for(int st_EC=51;st_EC<=150;)
    //            {cout<<seatingsEmpt[st_EC]<<"  "<<seatingsEmpt[st_EC+1]<<"  "<<seatingsEmpt[st_EC+2]<<"\n";
    //            st_EC=st_EC+3;}
    //         }
    //         else {cout<<"Error in Empty seats displaying.\n";}

    //     else{cout<<"code error in DispAll_Seats() func.\n"}
    // }
    // Displ_AsigndSeats()
    // {
    //     h;
    // }
   // friend class psngerQ;
};
class Qnde
{
    public:
    //int seats, TotlArcf;
    int ArcrSize_seats;//small=100, big=150
    Qnde *nxt; //if pointer to nxt added in below class, then pointers of those class wont contain *nxt in them which is required.
};
class Totl_Aircrft
{
    public://can name be same of this variable as in other class?
     Qnde *frnt, *rear, *prevRear/*, *curNd, *prevNd*/;
     Qnde *prevNd=frnt, *currNde=frnt;
     int TotlAc=0;
     int amount=0;//amount available to each deck that would be increased upon available aircraft Rent-outs and decrease upon Leasing. No more leasing can be done once amount finished.
   // Qnde* Details; //  no need as 
    // {// is this required inside this class or the outer node class created will work?
     Totl_Aircrft()
        :currNde(NULL),frnt(NULL), rear(NULL), prevNd(NULL), prevRear(NULL) {}

    Totl_Aircrft(int nmbAcr, Totl_Aircrft *Plob, int sze)
    {
        //Qnde* nmbArc;
        //nmbArc->ArcrSize_seats=nmb;
        for(int ac=nmbAcr; ac>0; ac--)
        {
            Plob->enqueue(sze);
        }        
    }
bool LeaseAirpl(int, int, int, Totl_Aircrft*);
    ~Totl_Aircrft()//why destructor returns random int?
        {
           // Nde *curNd, *tmpr = frnt; // no need for declaring?
           currNde=prevNd=frnt;
            if(!isEmpt())
            {while(currNde->nxt)
            {
                currNde=currNde->nxt;
                prevNd->nxt=NULL;
                delete prevNd;
                prevNd=currNde;
            }
          //tmpr->nxt=NULL;
          delete prevNd;}
          frnt=rear=prevNd=currNde=prevRear=NULL;
          TotlAc=0;
        }
    // int AircrNmbr(int nm, string arpl)//nm: nmbr of arcrfts   arpl: as string storing their type previously
    // {
    //     for(int an=1; an<=nm; an++)
    //     {
    //       if(head)
    //       {Qnde *curNd=head;}
    //       else
    //       {head=curNd=new Qnde;}
    //          if(arpl[an]=='s')
    //          {
    //              curNd->ctg='singlEngined_plane';
    //          }
    //          else if(arpl[an]=='d')//if 'dd' be added, will it be able to store it?
    //          {curNd->ctg='DoubleDecker';}
               
    //            if(an=nm)
    //            {tail=curNd;
    //            break;}
    //            else{continue;}
    //       curNd->nx=new Qnde;
    //       curNd=curNd->nx;  
    //     }
    //       //delete curNd;  no need as break statement added in tail assignment if statement.
    //  return ;
    //  }
        bool isEmpt()
        {if(TotlAc!=0)
        {return false;}
        else {return true;}}

     void enqueue(int NmbOfseatCrft)
        {
            Qnde *newNd=new Qnde();
            newNd->ArcrSize_seats=NmbOfseatCrft;
          //  newNd->serNo=totl;
            newNd->nxt=NULL;

            if(isEmpt())
            {frnt=newNd;
            rear=prevRear=newNd;}
            else
            {prevRear=rear;
            rear->nxt=newNd;
            rear=newNd;}
            TotlAc++;
        cout<<"";//insead of this, add a big statement dequeing ALL and if successful, do st and run statement like this.

        }
bool dequeue(int &ArcBig_sml)
        {
         //   Nde **tmpr=&curNd;
         Qnde *currNde;
            if(isEmpt())
            {
                std::cout<<"\n Queue of this Aircraft-Deck is Already Empty.! \n";
                return false;
            }
            else
            { // how *tmpr, Nde* and *details related?
                ArcBig_sml=frnt->ArcrSize_seats;
                currNde=frnt->nxt;

                delete frnt;
                frnt=currNde;
                TotlAc--;
            cout<<"";//insead of this, add a big statement dequeing ALL and if successful, do st and run statement like this.
                return true;
            }
        }
        

     bool delNd_acrMdl(int &AcrB_S/*, int seatt*/, Totl_Aircrft *obbj)
    {
       currNde=prevNd=frnt;
            if(/*isEmpt()*/currNde==NULL)
            {
                std::cout<<"-| This 'Aircraft-Deck' is Already Empty.!\n";
                return false;
            }
            else
            { // how *tmpr, Nde* and *details related?
                while(/*obbj->*/currNde)
                {
                   if(AcrB_S==currNde->ArcrSize_seats)//bcz being identified by its no.seats only.
                   {
                      if(currNde!=frnt)
                       {
                        prevNd->nxt=currNde->nxt;
                        currNde->nxt=NULL;
                        delete currNde;
                        prevNd=currNde=frnt;
                        TotlAc--;
                        cout<<"\n|The '"<<AcrB_S<<"' Aircraft have 'Successfully' been removed from this Deck "/*<<obbj->frnt*/<<" |..";
                        return true;
                       }
                      //  else
                      //  {
                      //   if(currNde->nxt)
                      //     {currNde=frnt->nxt;
                      //     frnt->nxt=NULL;
                      //     delete frnt;
                      //     frnt=prevNd=currNde;
                      //     TotlAc--;
                      //     cout<<"\n|The '"<<AcrB_S<<"' Aircraft have 'Successfully' been removed from this Deck "/*<<obbj->frnt*/<<" |..";
                      //    return true;}
                        else
                        {
                          // frnt->nxt=NULL;
                          // delete frnt;
                          // frnt=currNde=prevNd=rear=prevRear=NULL;
                          // TotlAc--;
                          // cout<<"\n|The '"<<AcrB_S<<"' Aircraft have 'Successfully' been removed from this Deck "/*<<obbj->frnt*/<<" |..";
                          // return true;
                          int dmm; bool dqq;
                          dqq=dequeue(dmm);
                          if(dqq)
                          {return true;}
    
                        }
                   }
 //  cout<<"\n|The Aircraft have 'Successfully' been removed from the Deck.."; // not here as it wont print bcz before it comes on this loop ever in execution which it would never once entered the if statement, it would return true as the final return value of the function and exit/finish.
                   
                 else
                   {prevNd=currNde;
                   currNde=currNde->nxt;}
                
            } }
         cout<<"\n Airplane with seats "<<AcrB_S<<" isn't standing in this Aircraft Deck. ||.";
         return false;
    }
    
     
     void Mke_Null(Totl_Aircrft *plOb)
        {
            //string dumNm, dumCtgr;
            int dumSt;
            while(!isEmpt())
            {plOb->dequeue(dumSt);}
            std::cout<<"\n | | This Aircraft Deck have been emptied!! |\n";
        }
        


     int CountArcrf(Totl_Aircrft *plnOb)
        {
            currNde=plnOb->frnt;
            int cntArcrf=0;
            while(currNde)
            {
                currNde=currNde->nxt;
                cntArcrf++;
            }
            TotlAc=cntArcrf;
            return cntArcrf;
        }
       bool travrsFr_Big(Totl_Aircrft *PlnObj)
       {//traversing& finding if Big airplane is available in the deck of airplanes(airplane object traversal)
        //curNd=frnt;
          while(currNde!=NULL && PlnObj/*->curNd->ArcrSize_seats!=150*/)
         {  if(PlnObj && PlnObj->currNde->ArcrSize_seats==150)//if big plane found
            {
                if(currNde==frnt)//delete that craft as being assigned to the passengers.
                {//can't we connect the objects so that they store in this same object instead of deleting permenantly? delete from queue but store first in another queue which is the boarding queue and assighn passengers to that very object.

                    currNde=currNde->nxt;
                    prevNd->nxt=NULL;
                    delete prevNd;
                    frnt=currNde;
                    TotlAc--;
                    cout<<"\nDouble Decker found & taken out of the Deck for passenger Loading....|..\n";
                    return true;
                }
                else
                {
                    prevNd->nxt=currNde->nxt;
                    currNde->nxt=NULL;
                    delete currNde;
                    TotlAc--;
                    cout<<"\nDouble Decker found & taken out of the Deck for passenger Loading....|..\n";
                    return true;
                }
             // return true;
            } 
            else if(currNde->nxt && PlnObj->currNde->ArcrSize_seats!=150)
             {//added !=150 to differentiate it from previous condition or else both could be true.
                prevNd=currNde;
                currNde=currNde->nxt;
               //travrsFr_Big(PlnObj); not needed or else curNd will point to front again. while loop will do its job instead.
             }
         else
          {cout<<"\n$Currently 'No Double Decker Available' in the Deck. Will need to lease it.\n";
          return false;}
         }
        // return false; can this be written here instead of up?
 {cout<<"\n$Currently 'No Double Decker Available' in the Deck. Will need to lease it.\n";
 return false; //if while loop exited before returning true, means not found as object finished.
 }
      
      }

//void travrsFr_Sml(Totl_Aircrft *PlnObj)                  {
       
       bool travrsFr_Sml(Totl_Aircrft *PlnObj)
       { //traversing& finding if small airplane is available in the deck of airplanes(airplane object traversal)
        prevNd=currNde=frnt;//will assign curNd to frnt on each func call
           while(currNde!=NULL && PlnObj/*&& PlnObj->curNd->ArcrSize_seats!=100*/)
           {
                 if(/*PlnObj && */PlnObj->currNde->ArcrSize_seats==100)//if small aircraft found
                 {
                      if(currNde==frnt)//delete that craft as being assigned to the passengers.
                      {//can't we connect the objects so that they store in this same object instead of deleting permenantly? delete from queue but store first in another queue which is the boarding queue and assighn passengers to that very object.
                        currNde=currNde->nxt;
                        prevNd->nxt=NULL;
                        delete prevNd;
                        frnt=currNde;
                        TotlAc--;
                        cout<<"\nSmall Airplane found & taken out of the Deck for passenger Loading....|..\n";
                        return true;
                     }
                     else
                     {
                        prevNd->nxt=currNde->nxt;
                        currNde->nxt=NULL;
                        delete currNde;
                        TotlAc--;
                        cout<<"\nSmall Airplane found & taken out of the Deck for passenger Loading....|..\n";
                        return true;
                     }
                 //  return true; 
                 } 
                 
                 else if(PlnObj->currNde->ArcrSize_seats!=100 && currNde->nxt)//how to know that curNd was at head in the beginning of all different objects??
                 {//added !=100 to differentiate it from previous condition or else both could be true.
                    prevNd=currNde;
                    currNde=currNde->nxt;
                    //travrsFr_Sml(PlnObj); not needed or else curNd will point to front again. while loop will do its job instead.
                 }
         
                 else
                 {cout<<"\n$Currently 'No Small Airplane Available' in the Deck. Will need to lease it.\n";
                  return false;}
           }
 {cout<<"\n$Currently 'No Small Airplane Available' in the Deck. Will need to lease it.\n";
 return false; //if while loop exited before returning true, means not found as object finished.
 }
// void travrsFr_Sml2(Totl_Aircrft *PlnObj)
// {
//     while(PlnObj->curNd!=NULL && PlnObj->curNd->ArcrSize_seats!=100)
//          {travrsFr_Sml(PlnObj);}
       }
       int /*Totl_Aircrft::*/RentOut_MyArp(Totl_Aircrft*, int, int, int);

};

class psngerQ
{
    public:
    //private:
    // struct psngrNd
    // {
    //     int cnic;
    //     char name, ctgory;
    //     psngerQ *nxt
    // };
    //psngerQ *nxt;
    Nde *rear, *frnt, *currNde, *tmpr;//Nde *nx
    int totl=0;
    int totlPnlt=0;
    public:
        int totlPsngr=0;
        psngerQ()
        :currNde(NULL),frnt(NULL), rear(NULL), tmpr(NULL) {}

        ~psngerQ()
        {
           // Nde *curNd, *tmpr = frnt; // no need for declaring?
           currNde=tmpr=frnt;
            if(!isEmpt())
            {while(/*!isEmpt()*/currNde->nxt)
            {
                currNde=currNde->nxt;
                tmpr->nxt=NULL;
                delete tmpr;
                tmpr=currNde;
            }
          //tmpr->nxt=NULL;
          delete tmpr;}
          frnt=rear=tmpr=currNde=NULL;
          totl=0;
          totlPsngr=0;
        }

        bool isEmpt()
        {if(totlPsngr==0)
        {return true;}
        else {return false;}}

        void enqueue(string nm, int nic, string ctgry, int seat)
        {
            Nde *newNd=new Nde();
            newNd->name=nm;
            newNd->cnic=nic;
            newNd->ctgory=ctgry;
            newNd->seatnmbr=seat;
          //  newNd->serNo=totl;
            newNd->nxt=NULL;

            if(isEmpt())
            {frnt=newNd;
            rear=newNd;}
            else
            {rear->nxt=newNd;
            rear=newNd;}
            totl++;
            totlPsngr++;
         cout<<"";//insead of this, add a big statement dequeing ALL and if successful, do st and run statement like this.
            //totlPsngr=totl; if this added, and a prefulled Q us there, TotlPsng will reduce to less when enqued falsely
        }


bool delNd_PsnQMdl(int &nic, psngerQ *Pobbj)
    {
       Nde *tmpr, *prevNd=frnt;
            if(isEmpt())
            {
                std::cout<<"-| This 'Passenger Queue' is Already Empty.!\n";
                return false;
            }
            else
            { // how *tmpr, Nde* and *details related?
                while(/*obbj->*/tmpr)
                {
                   if(tmpr->cnic==nic)//bcz being identified by its no.seats only.
                   {
                      if(tmpr!=frnt)
                       {
                        prevNd->nxt=tmpr->nxt;
                        tmpr->nxt=NULL;
                        delete tmpr;
                        prevNd=tmpr=frnt;
                        totlPsngr--;
                        cout<<"\n|The '"<<nic<<"' Passenger have 'Successfully' been removed from this Passenger Queue "/*<<obbj->frnt*/<<" |..";
                        return true;
                       }
                       else
                       {
                        tmpr=frnt->nxt;
                        frnt->nxt=NULL;
                        delete frnt;
                        frnt=prevNd=tmpr;
                        totlPsngr--;
                        cout<<"\n|The '"<<nic<<"' Passenger have 'Successfully' been removed from this Passenger Queue "/*<<obbj->frnt*/<<" |..";
                        return true;
                       }
 //  cout<<"\n|The Aircraft have 'Successfully' been removed from the Deck.."; // not here as it wont print bcz before it comes on this loop ever in execution which it would never once entered the if statement, it would return true as the final return value of the function and exit/finish.
                   }
                 else
                   {prevNd=tmpr;
                   tmpr=tmpr->nxt;}  
            } 
          cout<<"\n Passenger with CNIC "<<nic<<" isn't standing in this Passenger Queue.. |.";
          return false;
    }
    }


        bool dequeue(string &nm, int &nic, string &ctgry, int &seat)
        {
         //   Nde **tmpr=&curNd;
         Nde *tmpr;
            if(isEmpt())
            {
                std::cout<<"Passenger Queue is Already Empty.!\n";
                return false;
            }
            else
            { // how *tmpr, Nde* and *details related?
                nm=frnt->name;
                nic=frnt->cnic;
       
                ctgry=frnt->ctgory;
                seat=frnt->seatnmbr;
                tmpr=frnt->nxt;

                delete frnt;
                frnt=tmpr;
                totl--;
                totlPsngr--;
                //totlPsngr=totl;  
            cout<<"deqqsd";//insead of this, add a big statement dequeing ALL and if successful, do st and run statement like this.
                return true;
            }
        }
    // int seatRenpt(string apln, Nde *st_nm)//(int &seat) //psngerQ* int & seat
    // {//issue is with passing variables, its reach & interpretation.
    //     for(int ap=0;apln[ap]!='\0';ap++)
    //     {
    //         if(apln[ap]=='s')
    //         {
    //            PrsnDets->seatnmbr=st_nm;//this u must pass hardcoded to move.
    //            InsrtNdeBC(ndx, PrsnDets);
    //         }
    //         else if(apln[ap=='d'])
    //         {
    //            PrsnDets->seatnmbr=st_nm;
    //            InsrtNdeBC(ndx, PrsnDets);
    //         } 
    //         else {cout<<"Error in seatRenpt() func.\n"}
    //     }	
    //    return PrsnDets->seatnmbr;  return st_nm;
    // }
        void Mke_Null(psngerQ *psn)
        {
            string dumNm, dumCtgr;
            int dumNic, dumSt;
            while(!psn->isEmpt())
            {psn->dequeue(dumNm, dumNic, dumCtgr, dumSt);}
            //psngerQ *curNd;
            //curNd=frnt; these ops already done by dequeue
            //frnt=frnt->nxt;
            //delete curNd;//psngerQ *psngerQ::..
        }

        int CountPsngQ(psngerQ *PsnObj)
        {
            currNde=frnt;
            int cntPsng=0;
            while(currNde)
            {
                currNde=currNde->nxt;
                cntPsng++;
            }
            totlPsngr=cntPsng;
            return cntPsng;

            //return cntPsng;

        }
int Totlpnalty_Dtrmnr(int, int, psngerQ*);
void costEfficiencr(int, int, psngerQ*, Totl_Aircrft*, AcrftLnLst*);
//why when out of class, specifier isn't doing it's job?
};


bool Totl_Aircrft::LeaseAirpl(int NmbOfseat_inCrft, int amnDD, int amnSP, Totl_Aircrft *plObj)//rents desired airplane
{
    std::cout<<"\t--Leasing Airplane--\n\n";
    if(NmbOfseat_inCrft==150)
    {plObj->enqueue(NmbOfseat_inCrft);
    std::cout<<"'Double Decker' enqueued to the Deck as a LEASED PLANE.\n";
    amount=amount-amnDD;
    return true;}

    else if(NmbOfseat_inCrft==100)
    {plObj->enqueue(NmbOfseat_inCrft);
    std::cout<<"'Small aircraft' enqueued to the Deck as a LEASED PLANE.\n";
    amount=amount-amnSP;
    return true;}

    else
    {
        std::cout<<"....\tPlane of this type UNAVAILABLE! #\n";
        return false;
    }
//  psngerQ::costEfficiencr(pnlBC, pnlEC, PsnObj, plObj, StObj);
}

void psngerQ::costEfficiencr(int pnlBC, int pnlEC, psngerQ *PsnObj, Totl_Aircrft *plnObj, AcrftLnLst *StObj)
//if airplanes of both types remain but passengers are finshing, compare the profits of using small plane and paying 
//penalty to few with using big plane instead and paying no penalty. Profit where maximized be selected.
{
    int eff, psn, acr;
    int st, nic;
    string nm, ctg;
    // void ArcrfAlot_fly(int Totl_Aircrft::AircrNmbr , int )
    // {
    //     int;
    // }
   CountPsngQ(PsnObj);
    Nde *prsnDet;
    if(totlPsngr>=115)
    {
        bool trv=plnObj->travrsFr_Big(plnObj);
           if(trv)
           {               
              acr=150;
              plnObj->delNd_acrMdl(acr, /*150,*/ plnObj);
              for(int plnSt=1; !PsnObj->isEmpt() && plnSt!=151; plnSt++)
              {
                  PsnObj->dequeue(nm, nic, ctg, st);
                  prsnDet->cnic=nic;
                  prsnDet->name=nm;
                  prsnDet->ctgory=ctg;
                  prsnDet->seatnmbr=st;
                  //StObj->InsrtNdeBC
              
                       if(ctg=="Business")
                         {char dd='D';
                        //StObj=new AcrftLnLst('D');
                         Nde *crNd= StObj->Hd_BusinesClas;
                 //int seatt=StObj->FndNdeBC(curNd, nic); no as cnic not exist at that node and its traversing curnd.
                    
                //     if(crNd!=NULL && crNd->seatnmbr==st)
                //     {curNd-
                 
                //  }no need, below insrtNd will do the job.
                //  else
                //  {crNd=crNd->nxt;
                //  }
                         StObj->InsrtNdeBC(50, st, prsnDet);
                         }
                       else if(ctg=="Economy")
                         {
                          // StObj=new AcrftLnLst('D');
                          //AcrftLnLst(D);
                          Nde *crNd= StObj->Hd_EconmClas;
                          StObj->InsrtNdeEC(50, 150, st, prsnDet);
                         }
              }//operate big;
          }     //call same func; 
         else
         {bool lsr1=plnObj->LeaseAirpl(150, 120, 180, plnObj);
          if(lsr1)
          {costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, StObj);}
          //cout<<"Lease a Double Decker passing the same Deck as object & call me again!\n ";
          //Totl_Aircrft::LeaseAirpl(150, plnObj);
         
         /*costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, StObj);*/}
    }    //call same func;}
    else if(totlPsngr<115 && totlPsngr>100)
    {
       bool trv=plnObj->travrsFr_Sml (plnObj);
           if(trv==true)
           {
              acr=100;
              plnObj->delNd_acrMdl(acr/*, 100*/, plnObj);
              for(int plnSt=1; plnSt!=101; plnSt++)
              {
                  PsnObj->dequeue(nm, nic, ctg, st);
                  prsnDet->cnic=nic;
                  prsnDet->name=nm;
                  prsnDet->ctgory=ctg;
                  prsnDet->seatnmbr=st;
              
                       if(ctg=="Business")
                       {
                           //StObj=new AcrftLnLst('S');
                           //AcrftLnLst(S);
                           Nde *crNd= StObj->Hd_BusinesClas;
    
                           StObj->InsrtNdeBC(30, st, prsnDet);
                       }
                       else if(ctg=="Economy")
                       {
                         //AcrftLnLst(D);
                         Nde *crNd= StObj->Hd_EconmClas;
                         StObj->InsrtNdeEC(30, 100, st, prsnDet);
                       }
               }//operate small;
          }//call same func;
           else
           { bool lsr2=plnObj->LeaseAirpl(100, 120, 180, plnObj);
             if(lsr2)
             {costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, StObj);}
            //cout<<"Lease a Small Plane passing the same Deck as object & call me again!\n ";
           
           //Totl_Aircrft::LeaseAirpl(100, plnObj);
           /*costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, StObj);*/}//no need as psngQ!=NULL & belowest if will run executing this plus the penalty is also to be stored.
           //opearate small one for first 100 passengers;
     
           //pay penalty of remaining 1-14 passengers;
        Nde *prvN, *curNd=PsnObj->frnt;
        while(prvN!=PsnObj->rear)
        {
           if(curNd->ctgory=="Business")
           {curNd->penalty=pnlBC;}

           else if(curNd->ctgory=="Economy")
           {curNd->penalty=pnlEC;}
           else{std::cout<<"category nonexistant\n";}
        
        prvN=curNd;
        curNd=curNd->nxt;
       }
   
    // bool lsr=Totl_Aircrft::LeaseAirpl(100, plnObj);
    int TotP=psngerQ::Totlpnalty_Dtrmnr(pnlBC, pnlEC, PsnObj);
    std::cout<<" $ 💸💸Total Penalty for remaining passengers:  💸"<<TotP<<"$\n";
    }

   else if(totlPsngr<=100)
   {
      if(totlPsngr>40)
      { 
        int pssng=totlPsngr;
         if(plnObj->travrsFr_Sml(plnObj)==true)
         {
             acr=100;
             plnObj->delNd_acrMdl(acr,/* 100,*/ plnObj);
             cout<<"clrrrer";
             for(int plnSt=1; plnSt<pssng; plnSt++)
             {
                  PsnObj->dequeue(nm, nic, ctg, st);
                  prsnDet->cnic=nic;
                  prsnDet->name=nm;
                  prsnDet->ctgory=ctg;
                  prsnDet->seatnmbr=st;
              
                  if(ctg=="Business")
                  {
                  //AcrftLnLst(S);
                  Nde *crNd= StObj->Hd_BusinesClas;
                  StObj->InsrtNdeBC(30, st, prsnDet);
                  }
                  else if(ctg=="Economy")
                  {//AcrftLnLst(D);
                  Nde *crNd= StObj->Hd_EconmClas;                 
                  StObj->InsrtNdeEC(30, 100, st, prsnDet); 
                  }
             }//operate small;    
         }    //call same func;      
        else
        { bool lsr3=plnObj->LeaseAirpl(100, 120, 180, plnObj);
          if(lsr3)
          {costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, StObj);}
          //cout<<"Lease a Double Decker passing the same Deck as object & call me again!\n ";
                         
         //Totl_Aircrft::LeaseAirpl(100, plnObj);
         /*costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, StObj);*/}//no need as psngrQ finished & last else will execute.
      }
      else
      {//payPnalty of those;
       //Totlpnalty_Dtrmnr(pnl_BC, pnl_EC, psngerQ);
       //if(totlPnlt>=renting)
       //{rent small;
       //operate allocate it;}
       //else if(penalty of all<renting)
       //{pay penalty;
       //wait for next day new aircrafts return/enquing}
          
        Nde *prvN, *curNd=PsnObj->frnt;
        while(prvN!=PsnObj->rear)
        {
            if(curNd->ctgory=="Business")
            {curNd->penalty=pnlBC;}

            else if(curNd->ctgory=="Economy")
            {curNd->penalty=pnlEC;}
            else{std::cout<<"category nonexistant\n";}

          prvN=curNd;
          curNd=curNd->nxt;
        }
      int TotP=psngerQ::Totlpnalty_Dtrmnr(pnlBC, pnlEC, PsnObj);
      std::cout<<" $ 💸💸Total Penalty for remaining passengers:  💸"<<TotP<<"$\n";
      }
            //PsnObj->totlPsngr;   
   }
   
   CountPsngQ(PsnObj);
   if(PsnObj!=NULL && PsnObj->totlPsngr>40)
   {costEfficiencr(pnlBC, pnlEC, PsnObj, plnObj, /*AcrftLnLst **/StObj);}//StObj uncertainty,,
   
   else if(PsnObj->totlPsngr<40)
   {std::cout<<"✈️ % THE AIRPLANES HAVE BEEN EMPTIED IN THE DECK!\n ✈️Rest of the Passengers in this flight have been paid penalty & would travel in the next flight.\n\tWe appologize for the inconvenience.\n";}
   
   else
   {std::cout<<"✈️All Passengers Boarded!✈️✈️!\n";}
}
  // int pnltPaser()
  // {int pas;}



int psngerQ::Totlpnalty_Dtrmnr(int pnl_BC, int pnl_EC, psngerQ *psQ)//determines penalty to be paid for passengers being left behind without allocation and planes finished.
{//this is that psngrQ which wasn't dequeued due to aurcraft fininshed.
    //Nde *currNde=frnt;
  currNde=frnt;
  while(psQ->currNde)//->curNd necessary for loop to stop once curNd is NULL as PsQ will stilll remain true after curNd is NULL. 
    {  
        // if(currNde->cnic)
        // {
            if(currNde->ctgory=="Business")
            {totlPnlt=totlPnlt+pnl_BC;
            currNde->penalty=pnl_BC;}
            else if(currNde->ctgory=="Economy")
            {totlPnlt=totlPnlt+pnl_EC;
            currNde->penalty=pnl_EC;}
        //}
        currNde=currNde->nxt;
    }
    //    nmb of psngers left*pnl_BC;
    cout<<"$$ Total Penalty of this unboarded Passenger Queue to be paid is: $"<<totlPnlt<<"/- only.\n";
    return totlPnlt;
}

// int LeasOrBigSmal_operte(int seats) //comparer and optimal allocator as per profit.
// //checks if suppose a passenger is extra than small airplane while the available is only big (or small aircraft is available but passengers are more)
// //Is it better to operate big one or its better to lease the big one &rent a small one instead and paying penalty of (additional) that one passener.
// //& viceversa i.e, leasing the small one & renting a big one is optimal.

// {
//     if seats=150
//     {}
// }

int Totl_Aircrft::RentOut_MyArp(Totl_Aircrft *PlOb, int RntPrft_Pymsml, int RntPrft_Pymbig, int HwMny)//Rent outs' it
{
    int RntPy=0;
    int whicOn;
    int HwmFul=0;
        for(int dq=HwMny ;dq>0; dq--)
       {
        if(!PlOb->isEmpt())
        {    if(frnt->ArcrSize_seats==150)
            {
              PlOb->dequeue(whicOn);
              RntPy=RntPy+RntPrft_Pymbig;
              amount=amount+RntPrft_Pymbig;
             // std::cout<<"the extra Rented-Out Aircraft had "<<whicOn<<" seats, rented-out for $"<<RntPrft_Pymbig<<"\n";
            }
            else if(frnt->ArcrSize_seats==100)
            {
              PlOb->dequeue(whicOn);
              RntPy=RntPy+RntPrft_Pymsml;
              amount=amount+RntPrft_Pymsml;
              //std::cout<<"the extra Rented-Out Aircraft had "<<whicOn<<"seats, rented-out for $"<<RntPrft_Pymsml<<"\n";
            }
            HwmFul++;
        }
        else
        {
           int HwmLes=(HwMny-HwmFul); cout<<HwMny;
           std::cout<<"\nAirplanes available for rent-out are '"<<HwmLes<<"' less than demanded to Rent-Out.\n";
           std::cout<<"Thus all available which were '"<<HwmFul<<"' have been rented-Out.\n";
           std::cout<<"\n #  $Total rent received from this Deck is $"<<RntPy<<"/- only.\n";
           return RntPy;
        }
       }
    std::cout<<"\n #  $Total rent received from this Deck is $"<<RntPy<<"/- only.\n";
     return RntPy;
}
 
string randmStrnme_gen()
 {
    string NM;
    return NM;
 }

//allotment of passengers to those seat linklist hence filling the nodes
// MainWork: arcrft Auto allocation bsed on psngr, 

int main()
{
    //char dd='D', sm='S';
 
    // string nm, ct;
    // int ni, s;
    // pk->dequeue(&nm, &ni, &ct, &s);
    
    // pk.Mke_Null(pk);
    // bool chk;
    // chk=deck_pk.isEmpt();
    // if (pk.isEmpt()==false)
    // {cout<<"hahaah";}
    // else
   // {cout<<"nahan";}
            // Aircrft_Sml.InsrtNdeEC(30, 100, 4, &me);
            // Aircrft_Sml.InsrtNdeEC(30, 100, 4, &me);

//     Aircrft_Sml.Displ_ALLSeats(100, 30);
//  //deck_pk.enqueue(100);
//       int mjj=Aircrft_Sml.FndNdeBC(343);
 //     cout<<mjj;
   //  deck_pk.enqueue(100);
//      deck_pk.enqueue(100);
// // int dd=100;
// // bool ddd=deck_pk.dequeue(dd);
// if(ddd==true)
// {cout<<"dequed";}
      //int pnn=pk.Totlpnalty_Dtrmnr(20, 15, &pk);
//cout<<"\npnalty: "<<pnn<<endl;
//cout<<pk.frnt->penalty;
// cout<<"cost efficiencr:  \n";
// //pk.costEfficiencr(20, 15, &pk, &deck_pk, &Aircrft_Sml);
// cout<<"\nafter cosEff()";
//     //  if (mjj!=0)
//     //  {
//     //   cout<<"jajajjajjaaja";
//     //  }
//     //  else
//     //  {cout<<"popopopo";}

//   

   //deck_pk.dequeue(lp);
//      bool em=deck_pk.isEmpt();
//      if(em==false)
//      {cout<<"nooooo";}
//      else
//      {cout<<"baaabaa";}
//      cout<<"\t"<<deck_pk.TotlAc;
// int cn=deck_pk.CountArcrf(&deck_pk);
// cout<<" \n\nthisss"<<cn;
//      //deck_pk.Mke_Null(&deck_pk); 
// //deck_pk.travrsFr_Sml(&deck_pk);
// cout<<"\ntrrvr\n";//deck_pk.travrsFr_Sml(&deck_pk);
// int hw=deck_pk.RentOut_MyArp(&deck_pk, 222, 333, 2);
// cout<<"\n"<<hw<<endl;

//     //  pk.enqueue("hum", 343, "Business", 5);
//     // pk.~psngerQ();
// //int st, ni;
// //string nm, un;
// //pk.dequeue(nm, ni, un, st);
// bool mee=pk.isEmpt();
// int j=343;
// //pk.delNd_PsnQMdl(j, &pk);
// bool meb=pk.isEmpt();
// if(meb)
// //cout<<"noPass";
// else
// //cout<<"enqud\n";
// //deck_pk.~Totl_Aircrft();
// //pk.Mke_Null(&pk);
// //int cc=pk.CountPsngQ(&pk);//when destructor called before this, a random int will be returned here.
// //cout<<cc<<endl;
// //cout<<st<<nm;
//          Aircrft_Sml.Displ_ALLSeats(100, 30);

// // int lm=100;
// deck_pk.delNd_acrMdl(lm, &deck_pk);

// 

    //int n=deck_pk.frnt->ArcrSize_seats;

//     cout<<n;
// cout<<pk->totlPsngr;
//cout<<"ibkf";
  // pk.enqueue("hum", 42201, "Business", 1);
   // deck_pk.enqueue(100);
  //  cout<<"ibkf";

// Aircrft_Ful.Hd_BusinesClas->ctgory="Bu";
// cout<<Aircrft_Ful.Hd_BusinesClas->ctgory;

    //Aircrft_Sml.Displ_ALLSeats(100, 30);
    //Aircrft_Ful.Displ_ALLSeats(150, 50);

  //   Nde me;
  //  int k=150;
  //   me.seatnmbr=k;
  //           //cout<<"ibkf";
  //  me.cnic=343;
  //   me.ctgory="Business";
  //       me.name="Att";

    //me.seatnmbr=4;

    //Aircrft_Sml.InsrtNdeBC(30, me.seatnmbr, &me);
   //     cout<<"hyyy"<<endl;
      //      Aircrft_Sml.InsrtNdeBC(30, 4, &me);
//cout<<"naad";
        //    Aircrft_Sml.InsrtNdeBC(30, 4, &me);
          //  Aircrft_Sml.InsrtNdeEC(30, 100, 55, &me);
            //Aircrft_Sml.InsrtNdeEC(30, 100, 66, &me);
            //Aircrft_Sml.InsrtNdeEC(30, 100, 66, &me);
            //Aircrft_Sml.InsrtNdeEC(30, 100, 5, &me);
  
   AcrftLnLst Aircrft_FulPK1('D'), Aircrft_FulPK2('D'), Aircrft_FulPK3('D'), Aircrft_SmlPK1('S'); // 7funcs()
    //Aircrft_SmlPK1.Displ_ALLSeats(100, 30);
    //Aircrft_FulPK1.Displ_ALLSeats(150, 50);

    //Aircrft_Ful(D); why cant write this?
    psngerQ pk_bus, pk_eco, de, hr; // cstEffcn.
    Totl_Aircrft deck_pk, deck_de, deck_hr; 
    //Aircrft_FulPK1.Displ_ALLSeats(150, 50);
    cout<<endl;



                                              mt19937 generator{random_device{}()};
                                              //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
                                              uniform_int_distribution<int> distribution{'a', 'z'};
                                              auto generate_len = 6; //modify length according to your need
      
           int lp;
           deck_pk.enqueue(100);
      deck_pk.enqueue(100);
      deck_pk.enqueue(150);
      deck_pk.enqueue(150);
      int cnnt=deck_pk.CountArcrf(&deck_pk);
cout<<"\n Aircrafts in PK deck are: "<<cnnt;


           deck_pk.dequeue(lp);
           cout<<"Aircraft of size "<<lp<<" has been dequeued for passenger loading!. ";

 cnnt=deck_pk.CountArcrf(&deck_pk);
cout<<"\n Aircrafts in PK deck are: "<<cnnt;


        Nde pssng;                                      
for(int d=1; d<=50/*d<=522*/; d++)
{                                                 string rand_str(generate_len, '\0');
                                                  for(auto& dis: rand_str)
                                                  dis = distribution(generator);
  string cls;
  int sett;
 // if(/*d<=50 || d>=151&&d<=200 || d>301&&d<=350 || d>=451&&d<=472*/)
  {cls="Business"; pssng.ctgory="Business";
  sett=((rand()%50)+1);}
 // else
  //{cls="Economy"; 
 // sett=(((rand()%100)+50)+1);} //when small-plane, the insrtNd() will automatically generate seat range that is present for small plane instead of using this.                                           
  int num = ((rand() % 9000) + 1000);
  pk_bus.enqueue(rand_str, num, cls, sett);cout<<"\nnmb: "<<d;
}

for(int d=51; d<=100/*d<=522*/; d++)
{                                                 string rand_str(generate_len, '\0');
                                                  for(auto& dis: rand_str)
                                                  dis = distribution(generator);
  string cls;
  int sett;
 // if(/*d<=50 || d>=151&&d<=200 || d>301&&d<=350 || d>=451&&d<=472*/)
  //{cls="Business";
  //sett=((rand()%50)+1);}
 // else
  {cls="Economy"; pssng.ctgory="Economy";
  sett=(((rand()%100)+50)+1);} //when small-plane, the insrtNd() will automatically generate seat range that is present for small plane instead of using this.                                           
  int num = ((rand() % 9000) + 1000);
  pk_eco.enqueue(rand_str, num, cls, sett);cout<<"\nnmb: "<<d;
}


cout<<"\n\noutt!!";
int st, nic;
string ctg, nm;
for(int dq=10; dq<=50; dq++)
{
  pk_bus.dequeue(nm, nic, ctg, st);
cout<<"\n\nLKLKLKLKLKLKLKLK";
  pssng.seatnmbr=st;
  pssng.cnic=nic;
  pssng.ctgory=ctg;
  pssng.name=nm;
cout<<"\n\nAAASASAAAASA";
  if(dq<=50 /*pssng.ctgory=="Business"*/)
  {Aircrft_FulPK1.InsrtNdeBC(50, pssng.seatnmbr, &pssng);    cout<<"seconder issu";
  }

}


int lpp=150;
deck_pk.delNd_acrMdl(lpp, &deck_pk);

deck_pk.CountArcrf(&deck_pk);
cout<<"\n Aircrafts in PK deck are: "<<cnnt;

 bool km=deck_pk.delNd_acrMdl(lpp, &deck_pk);//when new declaration of other variable wasn't made and the same above was used, it didn't updated the values of cn, & em that shows it retrievs them in this compiler from cache, not operates again.      if(km==false)
     if(km)
     {cout<<"aircNot delted";}
     else
     {cout<<"arcf deleted";}
     cout<<"\t"<<deck_pk.TotlAc;


bool trr1=deck_pk.LeaseAirpl(100, 180, 120, &deck_pk);
if (trr1)
{cout<<"\nLease function Succesful!. Amount left = $"<<deck_pk.amount;}
trr1=deck_pk.LeaseAirpl(150, 180, 120, &deck_pk);
// bool trr2;
// if (trr2)
// {cout<<"\nLease function Succesful!. Amount left = $"<<deck_pk.amount;}
// int cnn2=0;
// cnn2=deck_pk.CountArcrf(&deck_pk);
// cout<<" \n\nNumber of aircraft Left in the deck: "<<cnn2;
deck_de.enqueue(150);
deck_de.enqueue(150);
deck_de.enqueue(100);
deck_de.enqueue(150);
cout<<"\nRemaining Aircrafts: \n"<<deck_de.TotlAc;

deck_de.travrsFr_Sml(&deck_de);
deck_de.travrsFr_Sml(&deck_de);

deck_de.LeaseAirpl(100, 180, 110, &deck_de);
deck_de.travrsFr_Sml(&deck_de);
deck_de.RentOut_MyArp(&deck_de, 110, 170, 4);


cout<<"\nRemaining Aircrafts: "<<deck_de.TotlAc;
Nde me;
me.cnic=42201;
me.ctgory="Business";
me.seatnmbr=5;
me.name="Humz";
Aircrft_SmlPK1.InsrtNdeBC(30, me.seatnmbr, &me);
Aircrft_SmlPK1.InsrtNdeBC(30, me.seatnmbr, &me);

Aircrft_SmlPK1.Displ_ALLSeats(100, 30);


int my=Aircrft_SmlPK1.FndNdeBC(42202);
cout<<endl<<my<<endl;

bool emm=Aircrft_SmlPK1.EmptyArcrf_bookngSS();
if(emm)
{cout<<"\nsuccesfully emptied the seat bookings.\n";}

bool emmp=pk_bus.isEmpt();
if(!emmp)
{cout<<"\nThis passenger Queue is not yet empty\n";}

int cntt=pk_bus.CountPsngQ(&pk_bus);
cout<<"The passengers here are: "<<cntt<<endl<<endl<<endl<<endl;

// Nde mmee;
// mmee.cnic=4422;
// mmee.ctgory="Business";
// mmee.name="Hum";
// mmee.seatnmbr=24;

// pk_bus.enqueue(mmee.name, mmee.cnic, mmee.ctgory, mmee.seatnmbr);

// pk_bus.delNd_PsnQMdl(mmee.cnic, &pk_bus);



pk_bus.Mke_Null(&pk_bus);
cout<<endl<<endl<<endl;
bool emmpp=pk_bus.isEmpt();
if(emmpp)
{cout<<"\nThis passenger Queue is now Empty\n";}

pk_bus.Totlpnalty_Dtrmnr(120, 170, &pk_bus);



// for(int dq=51; dq<=53; dq++)
// {
//   bool sss;
//   if(pk_eco.currNde)
//   {cout<<"errror with enqu";}
//   else
//   {cout<<"err wuth funnnc";}
  
//   pk_eco.dequeue(nm, nic, ctg, st);
// cout<<"\n\nECECECECEECE";
//   pssng.seatnmbr=st;
//   pssng.cnic=nic;
//   pssng.ctgory=ctg;
//   pssng.name=nm;
// cout<<"\n\nCNCNCNCNCNC";
//   if(pssng.ctgory=="Economy")
//   {Aircrft_FulPK1.InsrtNdeEC(50, 150, pssng.seatnmbr, &pssng);    cout<<"yppp gsu";
//   }
 //else if(dq>=51&&dq<=150)
 //{cout<<"loop end must fin";
 //Aircrft_FulPK1.InsrtNdeEC(50, 150, pssng.seatnmbr, &pssng);}

  //else if(dq>=151&&dq<=200)
  //{Aircrft_FulPK2.InsrtNdeBC(50, st, &pssng);}
  // else if(dq>=201&&dq<=300)
  // {Aircrft_FulPK2.InsrtNdeEC(50, 150, st, &pssng);}
  // else if(dq>301&&dq<=350)
  // {Aircrft_FulPK3.InsrtNdeBC(50, st, &pssng);}
  // else if(dq>=351&&dq<=450)
  // {Aircrft_FulPK3.InsrtNdeEC(50, 150, st, &pssng);}
  
  //  if(dq>=451&&dq<=472)
  // {Aircrft_SmlPK1.InsrtNdeBC(30, pssng.seatnmbr, &pssng);}
  // else if(dq>=473&&dq<=522)
  // {Aircrft_SmlPK1.InsrtNdeEC(30, 100, st, &pssng);}


    Aircrft_FulPK1.Displ_ALLSeats(150, 50);





    return 0;
}






//if BC are fully booked & passenger have that category, it will infinietely assign rand() & stuck in loop.

//have to check totlArcfQ only.

//in display(), the BorE even if passed correct will give error as BC & EC are separate linklists.

//the insertNodeBC must check first which seats are empty and must generate random seat from numbers excluding that one.

//InsertNdeBC must validate nic that same person isnt booking multiple seats on his name.

//In AirPlanRent(), we can add rental of choice like small or big plane. It will traverse the plane that many times and rent-out those ones only untill all finished.

//there is an unsolved issue that the plane neither dequeu() nor deleteMdl() the last lefted plane in the deck and instead thinks the deck is empty.

//if businees category is more than seats, the program mustn't dequeue & assign seats to him but must let it remain in the linklist and search for the remaining economy class passengers.

//The condition can be applied on leasArpln() where it would not allow to lease when amount is zero or less than a certain limit.




