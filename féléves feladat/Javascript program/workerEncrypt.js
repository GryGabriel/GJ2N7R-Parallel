self.onmessage = function(event){
    const characters = event.data[0];
    const charPerWorker = event.data[1];
    const text = event.data[2];
    const index = event.data[3];

    let start = 0;
    for(let i=0;i<index;i++){
        start += charPerWorker[i];
    }
    let end = start + charPerWorker[index];

    for(let i=start;i<end;i++){
        let line_count = 0;
        let index_in_text = 0;
        let final_index = 1;

        for(let j=0;j<text.length;j++){
            if(text[index_in_text] == '\n'){
                line_count++;
                final_index = 0;
            }

            if(text[index_in_text] == characters[i]){
                self.postMessage([line_count+1, final_index, i]);
                break;              
            }
            final_index++;
            index_in_text++;
        }
    }
}
