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

// Варианты цен (фильтры), которые ищет пользователь
let requiredRange1 = [null, 200];
let requiredRange2 = [100, 350];
let requiredRange3 = [200, null];

// сортировка при помощи метода Array.prototype.filter()
function requiredRanges(element, range){
    return ((element.prices[0] !== null && element.prices[0] >= range[0]) || range[0] === null) &&
        ((element.prices[1] !== null && element.prices[1] <= range[1]) || range[1] === null);
}

let result1 = courses.filter(element => requiredRanges(element, requiredRange1));
let result2 = courses.filter(element => requiredRanges(element, requiredRange2));
let result3 = courses.filter(element => requiredRanges(element, requiredRange3));

console.log(result1);
console.log(result2);
console.log(result3);

// Сортировка курсов по цене (в приоритете нижняя граница, затем верхняя граница)
let sortedCourses = JSON.parse(JSON.stringify(courses));

// для этого сначала отсортируем по возрастанию правой границы
sortedCourses.sort((a, b)=>{
    if(a.prices[1] === null) return 1;
    if(b.prices[1] === null) return -1;
    if(a.prices[1] - b.prices[1] > 0) return 1;
    if(a.prices[1] - b.prices[1] < 0) return -1;
    if(a.prices[1] - b.prices[1] === 0) return 0;
});

console.log(sortedCourses)

// потом во возрастанию левой границы
sortedCourses.sort((a, b)=>{
    if(a.prices[0] === null) return -1;
    if(b.prices[0] === null) return 1;
    if(a.prices[0] - b.prices[0] > 0) return 1;
    if(a.prices[0] - b.prices[0] < 0) return -1;
    if(a.prices[0] - b.prices[0] === 0) return 0;
});

console.log(sortedCourses)

