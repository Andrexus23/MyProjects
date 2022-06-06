let courses = [
    { name: "Courses in England", prices: [0, 100] },
    { name: "Courses in Germany", prices: [500, null] },
    { name: "Courses in Italy", prices: [100, 200] },
    { name: "Courses in Russia", prices: [null, 400] },
    { name: "Courses in China", prices: [50, 250] },
    { name: "Courses in USA", prices: [200, null] },
    { name: "Courses in Kazakhstan", prices: [56, 324] },
    { name: "Courses in France", prices: [null, null] },
];

let sortedCourses = JSON.parse(JSON.stringify(courses));

// реализован алгоритм быстрой сортировки, сортирующий массив по возрастанию левой границы
function printInfo(leq, currentItem, greater, n){
    console.log('\t'.repeat(n), "leq:");
    if(leq.length > 0) {
        for (let i = 0; i < leq.length; i++) {
            console.log('\t'.repeat(n), leq[i]);
        }
    } else{
        console.log('\t'.repeat(n), "[]");
    }
    console.log('\t'.repeat(n), "currentItem:", currentItem);
    console.log('\t'.repeat(n), "greater:");
    if(greater.length > 0) {
        for (let i = 0; i < greater.length; i++) {
            console.log('\t'.repeat(n), greater[i]);
        }
    } else{
        console.log('\t'.repeat(n), "[]");
    }
    console.log();
} // отладочные выводы, учитывающие глубину рекурсии.

function quickSort(array, n){
    if(array.length < 2) // условие выхода из рекурсии.
        return array;

    const index = Math.floor(Math.random()*array.length); // Math.random() вернёт вещественное число 0 <= n < 1
    const currentItem = array[index]; // currentItem - рандомный элемент массива
    const greater = []; // элементы, большие текущего
    const leq = []; // элементы, меньше, либо равные текущему

    for(let i = 0; i < array.length; i++){
        if(i === index){ // если рассматривается currentItem, то пропускаем его и не добавляем никуда
            continue;
        } // currentItem - контрольный элемент
        if(array[i].prices[0] > currentItem.prices[0] || (currentItem.prices[0] === null)){  // если левая граница текущего элемента больше контрольного элемента, то добавляем его в greater
            greater.push(array[i]);
        } else{
            leq.push(array[i]);
        }
    }

    printInfo(leq, currentItem, greater, n);

    return [ // вернём новый массив, состоящий из отсортированных leq, currentItem, greater
        ...quickSort(leq, n+1),
        currentItem,
        ...quickSort(greater, n+1)
    ];
}

sortedCourses = quickSort(sortedCourses, 0);
console.log("Sorted courses:\n", sortedCourses);



