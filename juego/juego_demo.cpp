#include <opencv/cvaux.h>
#include <opencv/highgui.h>


//using namespace std;
int main()
{
    ///// Pantalla presentacion
    CvSize size = cvSize(640,480);
    cvNamedWindow( "Presentacion", CV_WINDOW_AUTOSIZE  );
    IplImage *  inicio    = cvCreateImage(size, IPL_DEPTH_8U, 1);
    CvFont font1;
    double hScale1=1;
    double vScale1=1;
    int    lineWidth1=1;
    cvInitFont(&font1,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale1,vScale1,0,lineWidth1);
    cvPutText(inicio,"   HOLA! SOY DIANA BELTRAN    ", cvPoint(50,50),  &font1, cvScalar(200,200,250));
    cvPutText(inicio,"    BIENVENIDO A MI JUEGO     ", cvPoint(50,240), &font1, cvScalar(200,200,250));
    cvPutText(inicio,"PULSA UNA TECLA PARA CONTINUAR", cvPoint(50,430), &font1, cvScalar(200,200,250));

    cvShowImage("Presentacion", inicio);
    cvWaitKey(0);
    cvDestroyWindow( "Presentacion" );
    //////////////////////////////////////////////////////

     ////// Capturar video de la cámara
    CvCapture* capture = cvCaptureFromCAM( 0 );
    if( !capture )
    {
        fprintf( stderr, "ERROR: capture is NULL" );
            getchar();
            return -1;
    }
    // Crear una ventana para presentar las imagenes capturadas
    cvNamedWindow( "Mi_Juego", CV_WINDOW_AUTOSIZE );

    // Declaración variables

    CvPoint pt1, pt2, pt3, pt4, pt5, pt6, pt7;

    double width=size.width;
    double height=size.height;
    int rad=5;
    int t=8;
    int tb=2*rad+t;
    pt1.x =50;
    pt1.y = height/2-40;
    pt2.x =50;
    pt2.y =height/2+40;
    pt3.x =width-50;
    pt3.y = height/2-40;
    pt4.x =width-50;
    pt4.y =height/2+40;
    pt5.x =width/2;
    pt5.y = 0;
    pt6.x = width/2;
    pt6.y = height;
    srand(time(NULL));
    int cont=0;
    int cont1=0;
    int init=0;

    char c=' ';

    int num=rand()%50-25;

    if(num>=-8 && num<=8){
     num=rand()%15+10;
    }

    float ballSpeedx = num;
    float ballSpeedy = num;

    //Inicializa bola en el centro

    pt7.x = width/2;
    pt7.y = height/2;



    while( 1 )
    {
       // Obtener un frame
       IplImage* frame = cvQueryFrame( capture );
       if( !frame )
       {
        fprintf( stderr, "ERROR: frame is null..." );
        getchar();
        break;
       }

        ///Datos del juego
        CvFont font;
        double hScale=0.2;
        double vScale=0.8;
        int    lineWidth=1;
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);

        cvPutText (frame, "Jugador_1:", cvPoint(200,30), &font, cvScalar(0,0,255));
        cvPutText (frame, "Jugador_2:", cvPoint(338,30), &font, cvScalar(0,255,0));



       // Pintar segmentos
       cvLine(frame,pt1,pt2,CV_RGB(255,0,0),5);
       cvLine(frame,pt3,pt4,CV_RGB(0,255,0),5);
       cvLine(frame,pt5,pt6,CV_RGB(0,0,0),2);


       //Pintar la bola
       CvPoint center(pt7);
       cvCircle(frame, center, rad, CV_RGB(0,0,255), t, 8, 0 );


       // mover segmentos
       CvPoint pt13, pt14, pt15, pt16;
       c = cvWaitKey(100);
       int move=40;

       switch (c)

       {

        case 'S'://  Derecha
        if (pt1.y>0){
        pt1.y = pt1.y-move;
        pt2.y = pt2.y-move;
        }break;

        case 'Q': //  Izquierda
        if (pt2.y<height){
        pt1.y = pt1.y+move;
        pt2.y = pt2.y+move;
        }break;

        case 'R': // Arriba
        if (pt3.y>0){
        pt3.y =pt3.y-move;
        pt4.y = pt4.y-move;
        }break;

        case 'T':// Abajo
        if (pt4.y<height){
        pt3.y =pt3.y+move;
        pt4.y = pt4.y+move;
        }break;

       }

       // Cuando la bola toca paredes verticales suma puntos
       if (pt7.x-tb<0){
           cont1=cont1+1;
       }
       if (pt7.x+tb> width){
           cont=cont+1;
       }

       // Si la bola toca paredes verticales se devuelve
       if ( pt7.x-tb< 0 || pt7.x+tb >width  ){
         ballSpeedx = ballSpeedx* (-1);
       }

       // Si la bola toca paredes horizontales se devuelve
        if ( pt7.y-tb < 0 || pt7.y+tb>height ){
          ballSpeedy = ballSpeedy* (-1);
           }

       // Si la bola toca segmentos se devuelve
        if (((pt7.x-tb<pt1.x && pt7.x-tb>0) && (pt7.y+tb<=pt2.y && pt7.y+tb>=pt1.y)|| ((pt7.x+tb>pt3.x&&pt7.x+tb<width)&&(pt7.y+tb<=pt4.y && pt7.y-tb>=pt3.y)))){
           ballSpeedx = ballSpeedx* (-1);
           }
        pt7.x = pt7.x + ballSpeedx;
        pt7.y = pt7.y + ballSpeedy;

       // Dar puntaje al jugador
         switch (cont)

         {

          case 0:
          cvPutText (frame, "0", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 1:
          cvPutText (frame, "1", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 2:
          cvPutText (frame, "2", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 3:
          cvPutText (frame, "3", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 4:
          cvPutText (frame, "4", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 5:
          cvPutText (frame, "5", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 6:
          cvPutText (frame, "6", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 7:
          cvPutText (frame, "7", cvPoint(290,30), &font, cvScalar(0,0,255));

          break;

          case 8:
          cvPutText (frame, "8", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 9:
          cvPutText (frame, "9", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          case 10:
          cvPutText (frame, "10", cvPoint(290,30), &font, cvScalar(0,0,255));
          break;

          }

         switch (cont1)

         {

          case 0:
          cvPutText (frame, "0", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 1:
          cvPutText (frame, "1", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 2:
          cvPutText (frame, "2", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 3:
          cvPutText (frame, "3", cvPoint(429,30), &font, cvScalar(0,255,0));

          break;

          case 4:
          cvPutText (frame, "4", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 5:
          cvPutText (frame, "5", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 6:
          cvPutText (frame, "6", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 7:
          cvPutText (frame, "7", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 8:
          cvPutText (frame, "8", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 9:
          cvPutText (frame, "9", cvPoint(429,30), &font, cvScalar(0,255,0));
          break;

          case 10:
          cvPutText (frame, "10", cvPoint(429,30), &font, cvScalar(0,255,0));
           break;
         }

        // Informar hay una ganador

        if (cont==10)
        {
         cvPutText (frame, "          GANADOR JUGADOR 1             ", cvPoint(160,230), &font, cvScalar(255,255,0));
         cvPutText (frame, "            FIN DEL JUEGO               ", cvPoint(160,250), &font, cvScalar(255,255,0));
         cvPutText (frame, "  Pulsa Espacio para comenzar de nuevo  ", cvPoint(160,270), &font, cvScalar(255,255,0));
         cvPutText (frame, "          Pulsa q para salir            ", cvPoint(160,290), &font, cvScalar(255,255,0));
         pt7.x= width/2;
         pt7.y= height/2;
         if (c==' ')
          { cont=cont1=0;
          }
         }

        if (cont1==10)
        {
         cvPutText (frame, "          GANADOR JUGADOR 2             ", cvPoint(160,230), &font, cvScalar(255,255,0));
         cvPutText (frame, "            FIN DEL JUEGO               ", cvPoint(160,250), &font, cvScalar(255,255,0));
         cvPutText (frame, "  Pulsa Espacio para comenzar de nuevo  ", cvPoint(160,270), &font, cvScalar(255,255,0));
         cvPutText (frame, "          Pulsa q para salir            ", cvPoint(160,290), &font, cvScalar(255,255,0));
         pt7.x= width/2;
         pt7.y= height/2;
         if (c==' ')
         {
          cont=cont1=0;
         }
        }


          cvShowImage( "Mi_Juego", frame );

          // Vuele a inciar el juego//
          if (init==0)
          {
           cvPutText (frame, "PULSA UNA TECLA PARA EMPEZAR", cvPoint(180,270), &font, cvScalar(255,255,0));
           cvShowImage( "Mi_Juego", frame );
           cvWaitKey(0);
           }

          if( c=='q') break;

          init=init+1;
    }

          cvReleaseCapture( &capture );
          cvDestroyWindow( "Mi_Juego" );
         return 0;
  }
