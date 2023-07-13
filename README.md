The algorithm and the code heavily depend on the tqDist software http://birc.au.dk/software/tqDist/ and the tripVote software https://github.com/uym2/tripVote.git. We would like to thank the authors for the code and algorithmic ideas.

**Installation: using git**

```bash
git clone https://github.com/shayesteh99/optimal_SPR.git
cd Quartet_SPR
pip install -r requirements.txt
cd tripRoot
python setup.py build_ext -i
python setup.py install
cd ..
```

**Improving Trees Using Q-SPR**

Use ```improve_tree.py``` as shown below to improve tree using the SPR moves in Q-SPR:
``` bash
python improve_tree.py -i Example/s_tree.trees -r Example/truegenetrees -o Example/output
```
The imrpoved tree would be saved in ```Example/output/improved_tree.trees```.
You can also find the updated tree after each round in the ```Example/output/rounds/``` directory.

**Getting the SPR changes for each clade of a tree**

type the following command in the command line to learn how to use it.
``` bash
SPR_scores.py -h
```
