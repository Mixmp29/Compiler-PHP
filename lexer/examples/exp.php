<?php
    $min = 10000; 
    $numberA = 15;
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
        $numberA = $numberA + $numberB;
    }


    $numberB = $numberB + 15;
?>
