#include <iostream>
#include <cstdlib>

void move(int x1, int y1, int x2, int y2) { 
    int dx=x2-x1;
    int dy;
    if(dx!=0){
        if (dx>0){
            dy=y2-y1;
            if (dy!=0){
                if (dy>0){
                    if (dx>=dy){
                        int e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(true){
                            std::cout<<x1 <<" "<< y1 << std::endl;
                            x1++;
                            if (x1==x2){
                                break;
                            }
                            e=e-dy;
                            if(e<0){
                                y1=y1+1;
                                e=e+dx;
                            }
                        }
                    }
                    else{
                        int e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(true){
                            std::cout<<x1 <<" "<< y1 << std::endl;
                            y1++;
                            if (y1==y2){
                                break;
                            }
                            e=e-dx;
                            if(e<0){
                                x1=x1+1;
                                e=e+dy;
                            }
                        }
                    }
                }
                else{
                    if (dx>=-dy){
                        int e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(true){
                            std::cout<<x1 <<" "<< y1 << std::endl;
                            x1++;
                            if (x1==x2){
                                break;
                            }
                            e=e+dy;
                            if(e<0){
                                y1=y1-1;
                                e=e+dx;
                            }
                        }
                    }
                    else{
                        int e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(true){
                            std::cout<<x1 <<" "<< y1 << std::endl;
                            y1--;
                            if (y1==y2){
                                break;
                            }
                            e=e+dx;
                            if(e>0){
                                x1=x1+1;
                                e=e+dy;
                            }
                        }
                    }
                }
            }
            else{
                for (int x=x1; x<x2; x++){
                    std::cout<<x1 <<" "<< y1 << std::endl;
                }
            }
        }
        else{
            dy=y2-y1;
                if (dy!=0){
                    if (dy>0){
                        if (-dx>=dy){
                            int e=dx;
                            dx=e*2;
                            dy=dy*2;
                            while(true){
                                std::cout<<x1 <<" "<< y1 << std::endl;
                                x1--;
                                if (x1==x2){
                                    break;
                                }
                                e=e+dy;
                                if(e>=0){
                                    y1=y1+1;
                                    e=e+dx;
                                }
                            }
                        }
                        else{
                            int e=dy;
                            dy=e*2;
                            dx=dx*2;
                            while(true){
                                std::cout<<x1 <<" "<< y1 << std::endl;
                                y1++;
                                if (y1==y2){
                                    break;
                                }
                                e=e+dx;
                                if(e<=0){
                                    x1=x1-1;
                                    e=e+dy;
                                }
                            }
                        }
                    }
                    else{
                        if (dx<=dy){
                            int e=dx;
                            dx=e*2;
                            dy=dy*2;
                            while(true){
                                std::cout<<x1 <<" "<< y1 << std::endl;
                                x1--;
                                if (x1==x2){
                                    break;
                                }
                                e=e-dy;
                                if(e>=0){
                                    y1=y1-1;
                                    e=e+dx;
                                }
                            }
                        }
                        else{
                            int e=dy;
                            dy=e*2;
                            dx=dx*2;
                            while(true){
                                std::cout<<x1 <<" "<< y1 << std::endl;
                                y1--;
                                if (y1==y2){
                                    break;
                                }
                                e=e-dx;
                                if(e>=0){
                                    x1=x1-1;
                                    e=e+dy;
                                }
                            }
                        }
                    }
                }
                else{
                    for (int x=x1; x>x2; x--){
                        std::cout<<x1 <<" "<< y1 << std::endl;
                    }
                }
            }
        }
    else{
        int dy=y2-y1;
        if(dy!=0){
            if(dy>0){
                for (int y=y1;y<y2;y++){
                    std::cout<<x1 <<" "<< y1 << std::endl;
                }
            }
            else{
                for (int y=y1;y>y2;y--){
                    std::cout<<x1 <<" "<< y1 << std::endl;
                }
            }
        }
    }
}

int main(){
    move(10, 250, 495, 836);
    return 0;
}