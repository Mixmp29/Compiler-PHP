<?php
    $a = 0;
    $b = 1;

    $i = 0;

    $n = fgets(STDIN);
    
    while($i < $n)
    {
        $a = $a + $b;
        $b = $a - $b;
        $i = $i + 1;
    }

    print("Result: ");
    print($a);
?>
