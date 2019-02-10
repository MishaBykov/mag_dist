//
// Created by misha on 09.02.19.
//

#include "skeleton.h"

int main(int argc, char *argv[])
{
    Skeleton::init(
            "/home/misha/CLionProjects/mag_dist/example/4d/skeleton/p.ext "
            "--avisfukudaformat "
            "--silence "
            "--nologinfile "
            "--extinc "
            "--edges "
            "--ridges "
            );

    return 0;
}