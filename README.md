# Game-theoretic-network-simulator
GTNS is a discrete-event network simulator targeted primarily for research and educational use.  GTNS is written in Visual C++ programming language and supports different network topologies. This simulator was first produced to implement locally multipath adaptive routing (LMAR) protocol, classified as a new reactive distance vector routing protocol for MANETs. LMAR can find an ad-hoc path without selfish nodes and wormholes using an exhaustive search algorithm in polynomial time. Also when the primary path fails, it discovers an alternative safe path if network graph remains connected after eliminating selfish/malicious nodes. The key feature of LMAR to seek safe route free of selfish and malicious nodes in polynomial time is its searching algorithm and flooding stage that its generated traffic is equi-loaded compared to single-path routing protocols but its security efficiency to bypass the attacks is much better than the other multi-path routing protocols. LMAR concept is introduced to provide the security feature known as availability and a simulator has been developed to analyze its behavior in complex network environments [1]. Then we have added detection mechanism to the simulator, which can detect selfish nodes in network. The proposed algorithm is resilient against collision and can be used in networks which wireless nodes use directional antennas and it also defend against an attack that malicious nodes try to break communications by relaying the packets in a specific direction. Some game theoretic strategies to enforce cooperation in network have been implemented in GTNS, for example Forwarding-Ratio Strategy, TFT-Strategy and ERTFT. This tutorial helps new users to get familiar with GTNS and run different network scenarios.

# Citation

@inproceedings{farhat2010locally,
  title={Locally multipath adaptive routing protocol resilient to selfishness and wormholes},
  author={Farhat, Farshid and Pakravan, Mohammad-Reza and Salmasizadeh, Mahmoud and Aref, Mohammad-Reza},
  booktitle={International Conference on Information Security Practice and Experience},
  pages={187--200},
  year={2010},
  organization={Springer}
}

@inproceedings{tootaghaj2011game,
  title={Game-theoretic approach to mitigate packet dropping in wireless Ad-hoc networks},
  author={Tootaghaj, Diman Zad and Farhat, Farshid and Pakravan, Mohammad-Reza and Aref, Mohammad-Reza},
  booktitle={Consumer Communications and Networking Conference (CCNC), 2011 IEEE},
  pages={163--165},
  year={2011},
  organization={IEEE}
}

@inproceedings{tootaghaj2011risk,
  title={Risk of attack coefficient effect on availability of Ad-hoc networks},
  author={Tootaghaj, Diman Zad and Farhat, Farshid and Pakravan, Mohammad-Reza and Aref, Mohammad-Reza},
  booktitle={Consumer Communications and Networking Conference (CCNC), 2011 IEEE},
  pages={166--168},
  year={2011},
  organization={IEEE}
}
