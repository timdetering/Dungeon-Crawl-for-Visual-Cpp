/**
 * @file
 * @brief Brand/ench/etc effects that might alter something in an
 *             unexpected way.
**/

#ifndef FINEFF_H
#define FINEFF_H

class final_effect
{
public:
    final_effect(const actor *attack, const actor *defend, const coord_def &pos)
        : att(attack ? attack->mid : 0),
          def(defend ? defend->mid : 0),
          posn(pos)
    {
    }
    virtual ~final_effect() {}

    virtual bool mergeable(const final_effect &a) const = 0;
    virtual void merge(const final_effect &a)
    {
    }

    void schedule();
    virtual void fire() = 0;

protected:
    mid_t att, def;
    coord_def posn;
    actor *attacker() const { return actor_by_mid(att); }
    actor *defender() const { return actor_by_mid(def); }
};

class lightning_fineff : public final_effect
{
public:
    lightning_fineff(const actor *attack, const coord_def &pos)
        : final_effect(attack, 0, pos)
    {
    }
    bool mergeable(const final_effect &a) const;
    void fire();
};

class mirror_damage_fineff : public final_effect
{
public:
    mirror_damage_fineff(const actor *attack, const actor *defend, int dam)
        : final_effect(attack, defend, coord_def()), damage(dam)
    {
    }
    bool mergeable(const final_effect &a) const;
    void merge(const final_effect &a);
    void fire();
protected:
    int damage;
};

class trample_follow_fineff : public final_effect
{
public:
    trample_follow_fineff(const actor *attack, const coord_def &pos)
        : final_effect(attack, 0, pos)
    {
    }
    bool mergeable(const final_effect &a) const;
    void fire();
};

class blink_fineff : public final_effect
{
public:
    blink_fineff(const actor *blinker)
        : final_effect(0, blinker, coord_def())
    {
    }
    bool mergeable(const final_effect &a) const;
    void fire();
};

class distortion_tele_fineff : public final_effect
{
public:
    distortion_tele_fineff(const actor *defend)
        : final_effect(0, defend, coord_def())
    {
    }
    bool mergeable(const final_effect &a) const;
    void fire();
};

class trj_spawn_fineff : public final_effect
{
public:
    trj_spawn_fineff(const actor *attack, const actor *defend,
                     const coord_def &pos, int dam)
        : final_effect(attack, defend, pos), damage(dam)
    {
    }
    bool mergeable(const final_effect &a) const;
    void merge(const final_effect &a);
    void fire();
protected:
    int damage;
};

class blood_fineff : public final_effect
{
public:
    blood_fineff(const actor *defend, const coord_def &pos, int blood_amount)
        : final_effect(0, 0, pos), mtype(defend->type), blood(blood_amount)
    {
    }
    bool mergeable(const final_effect &a) const;
    void fire();
    void merge(const final_effect &a);
protected:
    monster_type mtype;
    int blood;
};

class deferred_damage_fineff : public final_effect
{
public:
    deferred_damage_fineff(const actor *attack, const actor *defend, int dam)
        : final_effect(attack, defend, coord_def()), damage(dam)
    {
    }
    bool mergeable(const final_effect &a) const;
    void merge(const final_effect &a);
    void fire();
protected:
    int damage;
};

class starcursed_merge_fineff : public final_effect
{
public:
    starcursed_merge_fineff(const actor *merger)
            : final_effect(0, merger, coord_def())
    {
    }
    bool mergeable(const final_effect &a) const;
    void fire();
};

void fire_final_effects();

#endif
