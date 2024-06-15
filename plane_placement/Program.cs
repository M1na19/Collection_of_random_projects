Enviroment env=new Enviroment("./env.json");
Fitness fn=new Fitness(env);
EvolutionaryAlgorithm ea;

ea = new EvolutionaryAlgorithm(env,true);
Airplane best=ea.Run();
File.WriteAllText("result.txt",best.GetFitness().ToString()+'\n'+best.ToString());