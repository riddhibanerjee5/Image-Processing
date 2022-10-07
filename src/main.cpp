#include <iostream>
#include <vector>
#include <string>
#include "TGA.cpp"
using namespace std;


void compareImageFiles(string fileOne, string fileTwo);
void Task1();
void Task2();
void Task3();
void Task4();
void Task5();
void Task6();
void Task7();
void Task8();
void Task9();
void Task10();
void ExtraCredit();


int main() {

    Task1(); // DONE
    Task2(); // DONE
    Task3(); // DONE
    Task4(); // DONE
    Task5(); // DONE
    Task6(); // DONE
    Task7(); // DONE
    Task8(); // DONE
    Task9(); // DONE
    Task10(); //DONE
    ExtraCredit(); // DONE

    return 0;
}

void Task1() {
    TGA* imgTop = new TGA();
    imgTop->ReadFromFile("input/layer1.tga");
    TGA* imgBottom = new TGA();
    imgBottom->ReadFromFile("input/pattern1.tga");

    imgTop->Multiply(imgBottom);
    imgTop->WriteToFile("output/part1.tga");

    // End of task verification
    cout << "Task 1 - " ;
    compareImageFiles("examples/EXAMPLE_part1.tga", "output/part1.tga");
}

void Task2() {
    TGA* imgTop = new TGA();
    imgTop->ReadFromFile("input/layer2.tga");
    TGA* imgBottom = new TGA();
    imgBottom->ReadFromFile("input/car.tga");

    imgBottom->Subtract(imgTop);
    imgBottom->WriteToFile("output/part2.tga");

    // End of task verification
    cout << "Task 2 - " ;
    compareImageFiles("examples/EXAMPLE_part2.tga", "output/part2.tga");
}

void Task3() {
    TGA* imgTop = new TGA();
    imgTop->ReadFromFile("input/layer1.tga");
    TGA* imgBottom = new TGA();
    imgBottom->ReadFromFile("input/pattern2.tga");

    imgTop->Multiply(imgBottom);

    TGA* imgScreen = new TGA();
    imgScreen->ReadFromFile("input/text.tga");
    imgScreen->Screen(imgTop);
    imgScreen->WriteToFile("output/part3.tga");

    //End of task verification
    cout << "Task 3 - " ;
    compareImageFiles("examples/EXAMPLE_part3.tga", "output/part3.tga");
}

void Task4(){
    TGA* imgTop = new TGA();
    imgTop->ReadFromFile("input/layer2.tga");
    TGA* imgBottom = new TGA();
    imgBottom->ReadFromFile("input/circles.tga");

    imgTop->Multiply(imgBottom);

    TGA* imgDifference = new TGA();
    imgDifference->ReadFromFile("input/pattern2.tga");
    imgTop->Subtract(imgDifference);
    imgTop->WriteToFile("output/part4.tga");


    cout << "Task 4 - " ;
    compareImageFiles("examples/EXAMPLE_part4.tga", "output/part4.tga");
}

void Task5() {
    TGA* imgTop = new TGA();
    imgTop->ReadFromFile("input/layer1.tga");
    TGA* imgBottom = new TGA();
    imgBottom->ReadFromFile("input/pattern1.tga");

    imgTop->Overlay(imgBottom);
    imgTop->WriteToFile("output/part5.tga");

    // End of task verification
    cout << "Task 5 - " ;
    compareImageFiles("examples/EXAMPLE_part5.tga", "output/part5.tga");
}

void Task6() {
    TGA* img = new TGA();
    img->ReadFromFile("input/car.tga");
    img->AddToChannel('G', 200);
    img->WriteToFile("output/part6.tga");

    // End of task verification
    cout << "Task 6 - " ;
    compareImageFiles("examples/EXAMPLE_part6.tga", "output/part6.tga");
}

void Task7() {
    TGA* img = new TGA();
    img->ReadFromFile("input/car.tga");
    img->MultiplyToChannel('R', 4);
    img->MultiplyToChannel('B', 0);
    img->WriteToFile("output/part7.tga");

    // End of task verification
    cout << "Task 7 - " ;
    compareImageFiles("examples/EXAMPLE_part7.tga", "output/part7.tga");
}

void Task8() {
    TGA* fromImg = new TGA();
    fromImg->ReadFromFile("input/car.tga");

    TGA* toImg = new TGA();
    fromImg->CopyHeaderTo(toImg);
    fromImg->CopyImageTo(toImg);

    fromImg->CopyOneChannelToAll('R', toImg);
    toImg->WriteToFile("output/part8_r.tga");

    fromImg->CopyOneChannelToAll('G', toImg);
    toImg->WriteToFile("output/part8_g.tga");

    fromImg->CopyOneChannelToAll('B', toImg);
    toImg->WriteToFile("output/part8_b.tga");


    // End of task verification
    cout << "Task 8 - " << endl;
    cout << "	r - " ;
    compareImageFiles("examples/EXAMPLE_part8_r.tga", "output/part8_r.tga");
    cout << "	g - " ;
    compareImageFiles("examples/EXAMPLE_part8_g.tga", "output/part8_g.tga");
    cout << "	b - " ;
    compareImageFiles("examples/EXAMPLE_part8_b.tga", "output/part8_b.tga");
}

void compareImageFiles(string fileOne, string fileTwo){
    TGA* img1 = new TGA();
    img1->ReadFromFile(fileOne);
    TGA* img2 = new TGA();
    img2->ReadFromFile(fileTwo);
    if (img1->compareHeader(img2) && img1->compareImage(img2)) {
//        cout << "SUCCESS - " << fileOne << " and " << fileTwo << " are identical!" << endl;
        cout << "......SUCCESS!" << endl;
    } else {
//        cout << "FAIL - " << fileOne << " and " << fileTwo << " are NOT identical!" << endl;
        cout << "......FAIL!" << endl;
    }
}

void Task9(){
    TGA* imgR = new TGA();
    imgR->ReadFromFile("input/layer_red.tga");

    TGA* imgOut = new TGA();
    imgR->CopyHeaderTo(imgOut);
    imgR->CopyImageTo(imgOut);

    imgR->CopyOneChannelToOne('R', imgOut);

    TGA* imgG = new TGA();
    imgG->ReadFromFile("input/layer_green.tga");
    imgG->CopyOneChannelToOne('G', imgOut);

    TGA* imgB = new TGA();
    imgB->ReadFromFile("input/layer_blue.tga");
    imgB->CopyOneChannelToOne('B', imgOut);

    imgOut->WriteToFile("output/part9.tga");

    // End of task verification
    cout << "Task 9 - " ;
    compareImageFiles("examples/EXAMPLE_part9.tga", "output/part9.tga");
}

void Task10(){
    TGA* origImg = new TGA();
    origImg->ReadFromFile("input/text2.tga");

    TGA* flipImg = new TGA();
    origImg->CopyHeaderTo(flipImg);
    origImg->CopyImageTo(flipImg);

    origImg->RotateImage(flipImg);

    flipImg->WriteToFile("output/part10.tga");

    // End of task verification
    cout << "Task 10 - " ;
    compareImageFiles("examples/EXAMPLE_part10.tga", "output/part10.tga");

}

void ExtraCredit() {
    TGA* img1 = new TGA();
    img1->ReadFromFile("input/text.tga");
    TGA* img2 = new TGA();
    img2->ReadFromFile("input/pattern1.tga");
    TGA* img3 = new TGA();
    img3->ReadFromFile("input/car.tga");
    TGA* img4 = new TGA();
    img4->ReadFromFile("input/circles.tga");

    TGA* imgTarget = new TGA();
    img1->CopyHeaderTo(imgTarget);
    imgTarget->InitializeImage(img1->getWidth() + img2->getWidth(), img1->getHeight()+img3->getHeight() );


    img1->CopySourceToTarget(img1, imgTarget, 0, 0);
    img1->CopySourceToTarget(img2, imgTarget, img1->getWidth(), 0);
    img1->CopySourceToTarget(img3, imgTarget, 0, img1->getHeight());
    img1->CopySourceToTarget(img4, imgTarget, img1->getWidth(), img1->getHeight());


    imgTarget->WriteToFile("output/extracredit.tga");

    // End of task verification
    cout << "Task ExtraCredit - " ;
    compareImageFiles("examples/EXAMPLE_extracredit.tga", "output/extracredit.tga");
}

