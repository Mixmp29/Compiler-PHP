<?php
$min = 10000;
$arr = array(5, 3, 6, 1, 2, 3, 4);
$numberA = 24;
$numberB = 21;

foreach ($arr as &$value) {
    if ($min > $value) :
        $min = $value;
    endif;
}

for ($i = 2;; ++$i) {
    if ($numberA % $i == 0 && $numberB % $i == 0) {
        $nod = $i;
        break;
    }
}

echo " наименьшое число " . $min;
echo " наименьшое общее число " . $nod;
?>
