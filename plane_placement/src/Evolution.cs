
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Data;

class EvolutionaryAlgorithm{
    Enviroment env;
    List<Airplane> population;

    bool debuger;
    public EvolutionaryAlgorithm(Enviroment env,bool debuger) {
        this.env = env;
        population = new List<Airplane>();
        this.debuger = debuger;
    }   
    public Airplane Run(){
        Fitness fn=new Fitness(env);
        Mutations mutagen=new Mutations(env);

        population=new List<Airplane>();
        while(population.Count<env.NrPopulation){
            population.Add(new Airplane(env));
        }
        List<Airplane>elitePopulation=new List<Airplane>();
        Airplane best=new Airplane(env);best.Evaluate(fn);
        for(int gen=0;gen<env.NrGenerations;gen++){
            Parallel.ForEach(population,specimen=>{
                specimen.Evaluate(fn);
            });

            population=population.OrderBy(x =>x.GetFitness()).ToList();

            float avgPerformance=0;
            for(int i=0;i<env.NrElite;i++){
                elitePopulation.Add(population[i]);
                avgPerformance+=population[i].GetFitness();
            }
            avgPerformance/=env.NrElite;
            population.Clear();
            
            int kids=0;
            int currentFather=0;
            int matingWith=0;
            while(population.Count<env.NrPopulation){
                if(currentFather!=matingWith && Succesor.Alikeness(elitePopulation[currentFather],elitePopulation[matingWith])>=env.AlikeThreshHold){
                    population.Add(mutagen.ApplyRandomMutation(Succesor.Kid(elitePopulation[currentFather],elitePopulation[matingWith])));
                    kids++;
                }
                matingWith++;
                if(matingWith>=env.NrElite){
                    currentFather++;
                    matingWith=0;
                    if(currentFather>=env.NrElite){
                        break;
                    }
                }
            }
            while(population.Count<env.NrPopulation){
                int randElite=Random.Shared.Next(0,env.NrElite);
                population.Add(mutagen.ApplyRandomMutation(Succesor.Kid(elitePopulation[randElite],new Airplane(env))));
            }

            if(best.GetFitness()>elitePopulation[0].GetFitness())best=elitePopulation[0].Clone();
            if(debuger==true){
                Console.WriteLine("Gen "+(gen+1).ToString()+"/"+env.NrGenerations.ToString()+": "+avgPerformance);
                Console.WriteLine("Kids from fit parents: "+kids.ToString());
                Console.WriteLine("New specimens: "+(env.NrPopulation-kids).ToString());
                Console.WriteLine("BEST: "+best.GetFitness().ToString());
                Console.WriteLine(best.ToString());
            }
            elitePopulation.Clear();
        }
        return best;
    }
}

sealed class Fitness{
    public int NrTests; 
    public float WalkTimeMax;
    public float WalkTimeMin;
    public float WaitTimeMax;
    public float WaitTimeMin;
    public float Value(Airplane a){
        float result = 0;
        for(int i=0;i<NrTests;i++){
            result+=this.Simulation(a);
        }
        return result/NrTests;
    }
    float Simulation(Airplane a){
        List<List<Airplane.Passanger>> passers = new List<List<Airplane.Passanger>>();
        for(int i=0;i<=a.NrGroups;i++){
            passers.Add(new List<Airplane.Passanger>());
        }
        foreach(var seat in a.GetPassangerConfig()){
            passers[seat.Value].Add(Airplane.Passanger.FromKey(seat.Key));
        }
        for(int i=0;i<a.NrGroups;i++){
            passers[i]=passers[i].OrderBy(_ => Random.Shared.Next()).ToList();
        }

        List<float> lockTime=new List<float>();
        HashSet<string> seated=new HashSet<string>();
        for(int row=0;row<=a.NrRows;row++){
            lockTime.Add(0);
        }
        foreach (var group in passers){
            foreach(var passer in group){
                //Assign values
                float movingSpeed=(float)NormalDistributeRandom(WalkTimeMin,WalkTimeMax);
                float waitTime=(float)NormalDistributeRandom(WaitTimeMin,WaitTimeMax);

                float time=0;
                for(int row=1;row<=passer.Row;row++){
                    lockTime[row]=Math.Max(time,lockTime[row])+movingSpeed;
                    time=lockTime[row];
                }

                float bonus=0;
                if(passer.Seat-'A'+1<=a.NrSeats/2){
                    for(char seat=Convert.ToChar('A'+a.NrSeats/2-1);seat>=passer.Seat;seat--){
                        if(seated.Contains(new Airplane.Passanger(passer.Row,seat).AsKey())){
                            bonus+=(float)NormalDistributeRandom(WaitTimeMin,WaitTimeMax);
                        }
                    }
                }else{
                    for(char seat=Convert.ToChar('A'+a.NrSeats/2);seat<=passer.Seat;seat++){
                        if(seated.Contains(new Airplane.Passanger(passer.Row,seat).AsKey())){
                            bonus+=(float)NormalDistributeRandom(WaitTimeMin,WaitTimeMax);
                        }
                    }
                }
                time+=waitTime+bonus;
                lockTime[passer.Row]=time;
                seated.Add(passer.AsKey());
            }
        }
        return lockTime.Max();
    }
    double NormalDistributeRandom(float min,float max){
        double u1=Random.Shared.NextDouble();
        double u2=Random.Shared.NextDouble();

        double z1=Math.Sqrt(-2*Math.Log(u1))*Math.Cos(2*Math.PI*u2);
        return 1/(1+Math.Exp(-z1))*(max-min)+min;
    }
    public Fitness(Enviroment env){
        NrTests=env.NrTests;
        WaitTimeMax=env.WaitTimeMax;
        WaitTimeMin=env.WaitTimeMin;
        WalkTimeMax=env.WalkTimeMax;
        WalkTimeMin=env.WalkTimeMin;
    }
}

sealed class Mutations{
    public int MaxSwitch{get;}
    public int ChanceGroupAdd{get; }
    public int ChanceGroupRemove{get;}

    public int ChanceSwitch{get; }
    public Airplane ApplyRandomMutation(Airplane a){
        int randMutation=Random.Shared.Next(0,100);

        Airplane mutated=new Airplane();
        if(randMutation<=ChanceGroupRemove && a.NrGroups>1){
            mutated=RemoveGroup(a);
        }else if(randMutation<=ChanceGroupAdd+ChanceGroupRemove){
            mutated=AddGroup(a);
        }else if(randMutation<=ChanceSwitch+ChanceGroupAdd+ChanceGroupRemove){
            mutated=SwapPassangers(a,Random.Shared.Next(0,MaxSwitch+1));
        }else{
            mutated=a.Clone();
        }
        return mutated;
    }
    Airplane AddGroup(Airplane original){
        Airplane mutated=original.Clone();
        mutated.CreateGroup();
        return mutated;
    }
    Airplane RemoveGroup(Airplane original){
        Airplane mutated=original.Clone();
        List<Airplane.Passanger> eliminated=mutated.RemoveRandomGroup();
        foreach(Airplane.Passanger pass in eliminated){
            int group=Random.Shared.Next(1, mutated.NrGroups+1);
            mutated.AddPassanger(pass,group);
        }
        return mutated;
    }
    Airplane SwapPassangers(Airplane original,int nr_swaps){
        Airplane mutated=original.Clone();
        for(int i=0;i<nr_swaps;i++){
            Airplane.Passanger pass=new Airplane.Passanger(Random.Shared.Next(1,mutated.NrRows+1), Convert.ToChar(Convert.ToInt32('A')+Random.Shared.Next(0,mutated.NrSeats)));
            mutated.RemovePassanger(pass);
            
            int new_group=Random.Shared.Next(1,mutated.NrGroups+1);
            mutated.AddPassanger(pass,new_group);
        }
        return mutated;
    }
    public Mutations(Enviroment env){
        MaxSwitch=env.MaxSwitch;
        ChanceGroupAdd=env.ChanceGroupAdd;
        ChanceGroupRemove=env.ChanceGroupRemove;
    }
}
sealed class Succesor{
    public static float NrGroupsBias=10;
    public static Airplane Kid(Airplane father,Airplane mother){
        Airplane kid=new Airplane();
        kid.NrRows=father.NrRows;
        kid.NrSeats=father.NrSeats;
        for(int row=1;row<=father.NrRows;row++){
            for(char seat='A';seat<'A'+father.NrSeats;seat++){
                Airplane.Passanger pass=new Airplane.Passanger(row,seat);

                int inherit=Random.Shared.Next(1,3);
                if(inherit==1){kid.NrGroups=Math.Max(kid.NrGroups,father.GetPassangerGroup(pass));kid.AddPassanger(pass,father.GetPassangerGroup(pass));}
                if(inherit==2){kid.NrGroups=Math.Max(kid.NrGroups,mother.GetPassangerGroup(pass));kid.AddPassanger(pass,mother.GetPassangerGroup(pass));}
            }
        }
        return kid;
    }
    public static float Alikeness(Airplane father,Airplane mother){
        float common=0;
        for(int row=1;row<=father.NrRows;row++){
            for(char seat='A';seat<'A'+father.NrSeats;seat++){
                Airplane.Passanger pass=new Airplane.Passanger(row,seat);
                if(father.GetPassangerGroup(pass)==mother.GetPassangerGroup(pass))common++;
            }
        }
        common-=NrGroupsBias*(father.NrGroups-mother.NrGroups);
        return common*100/(father.NrRows*father.NrSeats);
    }
}