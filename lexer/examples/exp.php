<?php
    $min = 10000; 
    $numberA = fgets(STDIN);
    $numberB = 21;
    $i = 0;

    if($numberA > $numberB)
    {
        while($i < 8)
        {
            $numberB = $numberB + 8;   
        }
    }
    else
    {
        $numberA = $numberA + 8;
    }


    $numberB = $numberB + 15;

    print("He is such good person");
    echo " Число B равно " . $min;

?>
