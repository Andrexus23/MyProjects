let input = {
  loanSum: 100000, // сумма кредита
  loanInterestRate: 13, // ставка
  loanTerm: 12 // срок
};


function roundNumber(x){
    if((typeof x) === "number") {
        if(parseFloat(x.toFixed(2)) === -0)
            return 0;
        return parseFloat(x.toFixed(2));
    }
    else
        return x;
}

function getAnnuityPaymentsSchedule(input){
  let result = [];
  var debt = input.loanSum;
  var monthlyInterest = (input.loanInterestRate)/(100*12);
  var monthlyPayment = debt * ((monthlyInterest)/(1-Math.pow(1+monthlyInterest, -input.loanTerm)));
  for(let i = 1; i <= input.loanTerm; i++){
      let month = i;
      let interestDebt = debt* monthlyInterest;
      let mainDebt = monthlyPayment - interestDebt;
      debt -= mainDebt;

      result.push({
          month: month,
          monthlyPayment: roundNumber(monthlyPayment),
          mainDebt: roundNumber(mainDebt),
          interestDebt: roundNumber(interestDebt),
          balanceOfPrincipal: roundNumber(debt)
      });
  }
  return result;
}

function printAnnuityPaymentsSchedule(arr){
    console.log('Месяц | Eжемесячный платёж | Основной долг | Долг по процентам | Остаток основного долга');
    for(let i = 0; i < input.loanTerm; i++) {
        console.log(
            arr[i].month + ' | ' +
            arr[i].monthlyPayment + ' | ' +
            arr[i].mainDebt + ' | ' +
            arr[i].interestDebt + ' | ' +
            arr[i].balanceOfPrincipal
        );
    }
}

let res = getAnnuityPaymentsSchedule(input);
printAnnuityPaymentsSchedule(res);