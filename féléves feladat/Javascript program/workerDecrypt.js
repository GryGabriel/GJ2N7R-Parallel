self.onmessage = function(event){
    const pairs = event.data[0];
    const pairsPerWorker = event.data[1];
    const text = event.data[2];
    const index = event.data[3];

    let start=0;
    for(let i=0;i<index;i++){
        start += pairsPerWorker[i];
    }
    let end = start + pairsPerWorker[index];

    for(let i=start;i<end;i++){
        const [row, column] = pairs[i].split(',');

        let index = 0;
        let line_count=0;
        while(line_count < row-1){
            if(text[index] === '\n'){
                line_count++;
            }
            index++;
        }
        index += parseInt(column)-1;
        self.postMessage([text[index], i]);
    }
  }